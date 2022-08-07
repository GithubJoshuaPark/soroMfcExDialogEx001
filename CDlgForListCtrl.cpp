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
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDlgForListCtrl::OnHdnItemclickList1)
END_MESSAGE_MAP()


// CDlgForListCtrl message handlers


BOOL CDlgForListCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_List.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	m_List.InsertColumn(1, _T("Desc"), LVCFMT_LEFT, 300);
	m_List.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);

	DWORD dwSeed = ::GetTickCount();
	LVITEM lvItem;
	::ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

	for (int i = 0; i < IMAGES_CNT; i++) {
		m_ImageListForNormal.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
		m_ImageListForSmall.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));

		CString ls_str = _T("");
		ls_str.Format(_T("[%d]th Item"), i+1);

		lvItem.pszText = ls_str.GetBuffer();
		lvItem.iItem = i;
		lvItem.iImage = i;
		lvItem.lParam = dwSeed + i;  // kind of PK among LVITEMs

		//m_List.InsertItem(i, ls_str, i);
		m_List.InsertItem(&lvItem);
		m_List.SetItemText(i, 1, ls_str);
	}

	m_List.SetImageList(&m_ImageListForNormal, LVSIL_NORMAL);
	m_List.SetImageList(&m_ImageListForSmall, LVSIL_SMALL);

	DWORD dwExStyle = m_List.GetExtendedStyle();
	m_List.SetExtendedStyle(dwExStyle | 
							LVS_EX_CHECKBOXES | 
							LVS_EX_FULLROWSELECT | 
							LVS_EX_GRIDLINES |
							LVS_EX_HEADERDRAGDROP);
	m_bAscending = FALSE;

	m_List.SortItems(&CDlgForListCtrl::CompareItem, (DWORD_PTR)this);
	UpdateArrow();

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

// MARK: - CListCtrl 헤더 부 클릭 시 Sorting 함수에서 호출
int CALLBACK CDlgForListCtrl::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CDlgForListCtrl* pDlg = (CDlgForListCtrl*)lParamSort;

	LVFINDINFO lvFind1, lvFind2;
	lvFind1.flags = LVFI_PARAM;
	lvFind1.lParam = lParam1;

	lvFind2.flags = LVFI_PARAM;
	lvFind2.lParam = lParam2;

	int nIndex1 = pDlg->m_List.FindItem(&lvFind1);
	int nIndex2 = pDlg->m_List.FindItem(&lvFind2);

	CString strText1 = pDlg->m_List.GetItemText(nIndex1, 0);
	CString strText2 = pDlg->m_List.GetItemText(nIndex2, 0);

	int nResult = 0;
	if (pDlg->m_bAscending) nResult = strText2.Compare(strText1);
	else nResult = strText1.Compare(strText2);

	return nResult;
}



void CDlgForListCtrl::UpdateArrow()
{
	// TODO: Add your implementation code here.
	CHeaderCtrl* pHeaderCtrl = m_List.GetHeaderCtrl();
	HDITEM hdItem;
	TCHAR szBuffer[256];
	::ZeroMemory(&hdItem, sizeof(hdItem));
	::ZeroMemory(szBuffer, 256);

	hdItem.mask = -1;                             // ①
	hdItem.pszText = szBuffer;
	hdItem.cchTextMax = 256;
	
	pHeaderCtrl->GetItem(0, &hdItem);

	hdItem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);   // ②

	if (m_bAscending) hdItem.fmt |= HDF_SORTDOWN; // ③
	else hdItem.fmt |= HDF_SORTUP;

	pHeaderCtrl->SetItem(0, &hdItem);
}


void CDlgForListCtrl::OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (phdr->iItem == 0)
	{
		m_bAscending = !m_bAscending;
		UpdateArrow();
		m_List.SortItems(&CDlgForListCtrl::CompareItem, (DWORD_PTR)this);
	}
	*pResult = 0;
}
