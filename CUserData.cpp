// CUserData.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "CUserData.h"


// CUserData

IMPLEMENT_DYNAMIC(CUserData, CWnd)

CUserData::CUserData()
{

}

CUserData::~CUserData()
{
}


BEGIN_MESSAGE_MAP(CUserData, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CUserData message handlers




void CUserData::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages

	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(0, 0, 255));
}


void CUserData::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect r;
	r.SetRect(point.x - 10, point.y - 10, point.x + 10, point.y + 10);

	CClientDC dc(this);
	dc.FillSolidRect(r, RGB(255,0,0));


	CWnd::OnLButtonDown(nFlags, point);
}
