// CSubClassTestWnd.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "CSubClassTestWnd.h"


// CSubClassTestWnd

IMPLEMENT_DYNAMIC(CSubClassTestWnd, CWnd)

CSubClassTestWnd::CSubClassTestWnd()
{
	m_bFlag = FALSE;
}

CSubClassTestWnd::~CSubClassTestWnd()
{
}


BEGIN_MESSAGE_MAP(CSubClassTestWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CSubClassTestWnd message handlers




void CSubClassTestWnd::OnPaint()
{
	CWnd::OnPaint();

	CClientDC dc(this); // device context for painting  ¡Ø CClientDC
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CRect cRect(3, 3, 16, 16);
	if (m_bFlag) dc.FillSolidRect(&cRect, RGB(192, 0, 0));
	else dc.FillSolidRect(&cRect, RGB(255,255,255));
}


void CSubClassTestWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);

	CRect cRect(3, 3, 16, 16);
	if (PtInRect(&cRect, point))
	{
		m_bFlag = !m_bFlag;
		RedrawWindow();
	}
}


void CSubClassTestWnd::OnDestroy()
{
	UnsubclassWindow();

	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}
