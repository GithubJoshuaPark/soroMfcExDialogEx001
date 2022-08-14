#include "pch.h"
#include "CBufferDC.h"

IMPLEMENT_DYNAMIC(CBufferDC, CDC)

CBufferDC::CBufferDC(CWnd* pParent) 
	: m_pParent(pParent) 
{
	ASSERT(pParent);

	// 대상 윈도우에 대한 정보 수집
	m_pTarget = m_pParent->BeginPaint(&m_PaintStruct);  // BeginPaint

	m_pParent->GetClientRect(&m_RcClient);
	m_pParent->GetWindowRect(&m_RcWindow);

	// 대상 윈도우에 대한 dc생성
	m_MemoryDC.CreateCompatibleDC(m_pTarget);

	// 대상 dc에 대한 메모리 비트맵 생성, 선택
	m_MemoryBmp.CreateBitmap(m_RcClient.Width(), m_RcClient.Height(),
		m_MemoryDC.GetDeviceCaps(PLANES),
		m_MemoryDC.GetDeviceCaps(BITSPIXEL), 0);

	m_pOldMemoryBmp = m_MemoryDC.SelectObject(&m_MemoryBmp);

	Attach(m_MemoryDC);
}

CBufferDC::~CBufferDC() {
	// 메모리 dc의 내용을 대상 윈도우에 출력
	// 내부적으로 비트맵을 출력한 것이므로 해당 비트맵을 1:1로 복사
	m_pTarget->BitBlt(
		m_PaintStruct.rcPaint.left,
		m_PaintStruct.rcPaint.top,
		m_PaintStruct.rcPaint.right - m_PaintStruct.rcPaint.left,
		m_PaintStruct.rcPaint.bottom - m_PaintStruct.rcPaint.top,
		&m_MemoryDC,
		m_PaintStruct.rcPaint.left,
		m_PaintStruct.rcPaint.top, SRCCOPY);

	m_MemoryDC.SelectObject(m_pOldMemoryBmp);

	m_pParent->EndPaint(&m_PaintStruct);  // EndPaint

	Detach();
}

//////////////////////////////////////////////////////////////////////
BOOL CBufferDC::Attach(HDC hDC)
{
	return CDC::Attach(hDC);
}

//////////////////////////////////////////////////////////////////////
HDC CBufferDC::Detach()
{
	return CDC::Detach();
}