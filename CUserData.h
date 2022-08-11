#pragma once

#define M_CUSERDATA_ID 123456

// CUserData

class CUserData : public CWnd
{
	DECLARE_DYNAMIC(CUserData)

public:
	CUserData();
	virtual ~CUserData();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


