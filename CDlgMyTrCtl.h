#pragma once
#include "afxdialogex.h"


// CDlgMyTrCtl dialog

class CDlgMyTrCtl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMyTrCtl)

public:
	CDlgMyTrCtl(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgMyTrCtl();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FOR_TREECTL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
