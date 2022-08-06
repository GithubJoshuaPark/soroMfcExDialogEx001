// CDlgHasUserClass.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "afxdialogex.h"
#include "CDlgHasUserClass.h"


// CDlgHasUserClass dialog

IMPLEMENT_DYNAMIC(CDlgHasUserClass, CDialogEx)

CDlgHasUserClass::CDlgHasUserClass(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CDlgHasUserClass::~CDlgHasUserClass()
{
}

void CDlgHasUserClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHasUserClass, CDialogEx)
END_MESSAGE_MAP()


// CDlgHasUserClass message handlers


BOOL CDlgHasUserClass::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_CUserData.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		CRect(50, 50, 200, 200), this, M_CUSERDATA_ID);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
