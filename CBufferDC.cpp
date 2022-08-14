#include "pch.h"
#include "CBufferDC.h"

IMPLEMENT_DYNAMIC(CBufferDC, CDC)

CBufferDC::CBufferDC(CWnd* pParent) 
	: m_pParent(pParent) 
{
	ASSERT(pParent);

	// ��� �����쿡 ���� ���� ����
	m_pTarget = m_pParent->BeginPaint(&m_PaintStruct);  // BeginPaint

	m_pParent->GetClientRect(&m_RcClient);
	m_pParent->GetWindowRect(&m_RcWindow);

	// ��� �����쿡 ���� dc����
	m_MemoryDC.CreateCompatibleDC(m_pTarget);

	// ��� dc�� ���� �޸� ��Ʈ�� ����, ����
	m_MemoryBmp.CreateBitmap(m_RcClient.Width(), m_RcClient.Height(),
		m_MemoryDC.GetDeviceCaps(PLANES),
		m_MemoryDC.GetDeviceCaps(BITSPIXEL), 0);

	m_pOldMemoryBmp = m_MemoryDC.SelectObject(&m_MemoryBmp);

	Attach(m_MemoryDC);
}

CBufferDC::~CBufferDC() {
	// �޸� dc�� ������ ��� �����쿡 ���
	// ���������� ��Ʈ���� ����� ���̹Ƿ� �ش� ��Ʈ���� 1:1�� ����
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