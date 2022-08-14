#pragma once


// CSubClassTestWnd

class CSubClassTestWnd : public CWnd
{
	DECLARE_DYNAMIC(CSubClassTestWnd)

public:
	CSubClassTestWnd();
	virtual ~CSubClassTestWnd();

	BOOL m_bFlag;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


