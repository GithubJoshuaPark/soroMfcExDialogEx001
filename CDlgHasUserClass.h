#pragma once
#include "afxdialogex.h"
#include "CUserData.h"


// CDlgHasUserClass dialog

class CDlgHasUserClass : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHasUserClass)
private:
	CUserData m_CUserData;

public:
	CDlgHasUserClass(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgHasUserClass();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
