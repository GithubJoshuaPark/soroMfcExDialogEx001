// CDlgForListCtrl.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "afxdialogex.h"
#include "CDlgForListCtrl.h"


// CDlgForListCtrl dialog

IMPLEMENT_DYNAMIC(CDlgForListCtrl, CDialogEx)

CDlgForListCtrl::CDlgForListCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_ImageListForNormal.Create(48, 48, ILC_COLOR32 | ILC_MASK, IMAGES_CNT, 1);
	m_ImageListForSmall.Create(16, 16, ILC_COLOR32 | ILC_MASK, IMAGES_CNT, 1);
}

CDlgForListCtrl::~CDlgForListCtrl()
{
}

void CDlgForListCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_CHECK1, m_CheckStatus);
}


BEGIN_MESSAGE_MAP(CDlgForListCtrl, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgForListCtrl::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgForListCtrl::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDlgForListCtrl::OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, &CDlgForListCtrl::OnLvnEndlabeleditList1)
END_MESSAGE_MAP()


// CDlgForListCtrl message handlers


BOOL CDlgForListCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_List.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	m_List.InsertColumn(1, _T("Desc"), LVCFMT_LEFT, 300);

	for (int i = 0; i < IMAGES_CNT; i++) {
		m_ImageListForNormal.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
		m_ImageListForSmall.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));

		CString ls_str = _T("");
		ls_str.Format(_T("[%d]th Item"), i+1);
		m_List.InsertItem(i, ls_str, i);
		m_List.SetItemText(i, 1, ls_str);
	}

	m_List.SetImageList(&m_ImageListForNormal, LVSIL_NORMAL);
	m_List.SetImageList(&m_ImageListForSmall, LVSIL_SMALL);

	DWORD dwExStyle = m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgForListCtrl::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	int li_status = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	switch (li_status)
	{
	case BST_CHECKED:
		m_List.SetView(LV_VIEW_SMALLICON);
		break;
	case BST_INDETERMINATE:
		m_List.SetView(LV_VIEW_ICON);
		break;
	case BST_UNCHECKED:
		m_List.SetView(LVS_REPORT);
		break;
	default:
		break;
	}
}


void CDlgForListCtrl::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int nCnt = m_List.GetItemCount();
	for (int i = nCnt; i >= 0; i--) {
		if (m_List.GetCheck(i)) m_List.DeleteItem(i);
	}
}


void CDlgForListCtrl::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CDlgForListCtrl::OnLvnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString ls_str = _T("");
	CEdit* pEdit = m_List.GetEditControl();
	pEdit->GetWindowTextW(ls_str);

	m_List.SetItemText(pDispInfo->item.iItem, 0, ls_str);


	*pResult = 0;
}
