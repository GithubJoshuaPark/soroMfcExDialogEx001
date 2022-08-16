// CDlgForListCtrlMove.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "afxdialogex.h"
#include "CDlgForListCtrlMove.h"


// CDlgForListCtrlMove dialog

IMPLEMENT_DYNAMIC(CDlgForListCtrlMove, CDialogEx)

CDlgForListCtrlMove::CDlgForListCtrlMove(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FOR_LISTCTL_02, pParent)
{
	m_ImageListForNormal.Create(48, 48, ILC_COLOR32 | ILC_MASK, IMAGES_CNT, 1);
	m_ImageListForSmall.Create(16, 16, ILC_COLOR32 | ILC_MASK, IMAGES_CNT, 1);

	hIcon = (HICON)LoadImage(
				AfxGetApp()->m_hInstance, 
				MAKEINTRESOURCE(IDI_ICON8), 
				IMAGE_ICON, 24, 24, 
				LR_DEFAULTCOLOR );
}

CDlgForListCtrlMove::~CDlgForListCtrlMove()
{
}

void CDlgForListCtrlMove::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListLeft);
	DDX_Control(pDX, IDC_LIST2, m_ListRight);
	DDX_Control(pDX, IDC_CHECK1, m_CheckStatus);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Control(pDX, IDC_ANIMATE1, m_Avi);
}


BEGIN_MESSAGE_MAP(CDlgForListCtrlMove, CDialogEx)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, &CDlgForListCtrlMove::OnLvnEndlabeleditList1)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST2, &CDlgForListCtrlMove::OnLvnEndlabeleditList2)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDlgForListCtrlMove::OnHdnItemclickList1)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgForListCtrlMove::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgForListCtrlMove::OnBnClickedButton1)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &CDlgForListCtrlMove::OnLvnBegindragList1)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgForListCtrlMove::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgForListCtrlMove::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDlgForListCtrlMove message handlers


BOOL CDlgForListCtrlMove::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_Avi.Open(IDR_AVI1);
	m_Avi.Play(0, -1, -1);

	m_nIndexLeftSel = -1;

	m_btn.SetIcon(hIcon);

	m_ListLeft.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	m_ListLeft.InsertColumn(1, _T("Desc"), LVCFMT_LEFT, 300);
	m_ListLeft.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	m_ListRight.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	m_ListRight.InsertColumn(1, _T("Desc"), LVCFMT_LEFT, 300);
	m_ListRight.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	DWORD dwSeed = ::GetTickCount();
	LVITEM lvItem;
	::ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

	for (int i = 0; i < IMAGES_CNT; i++) {
		m_ImageListForNormal.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
		m_ImageListForSmall.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));

		CString ls_str = _T("");
		ls_str.Format(_T("[%d]th Item"), i + 1);

		lvItem.pszText = ls_str.GetBuffer();
		lvItem.iItem = i;
		lvItem.iImage = i;
		lvItem.lParam = dwSeed + i;  // kind of PK among LVITEMs

		//m_List.InsertItem(i, ls_str, i);
		m_ListLeft.InsertItem(&lvItem);
		m_ListLeft.SetItemText(i, 1, ls_str);
	}

	m_ListLeft.SetImageList(&m_ImageListForNormal, LVSIL_NORMAL);
	m_ListLeft.SetImageList(&m_ImageListForSmall, LVSIL_SMALL);

	m_ListRight.SetImageList(&m_ImageListForNormal, LVSIL_NORMAL);
	m_ListRight.SetImageList(&m_ImageListForSmall, LVSIL_SMALL);

	DWORD dwExStyle = m_ListLeft.GetExtendedStyle();
	m_ListLeft.SetExtendedStyle(dwExStyle |
		LVS_EX_CHECKBOXES |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP);

	m_ListRight.SetExtendedStyle(dwExStyle |
		LVS_EX_CHECKBOXES |
		LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP);

	m_bAscending = FALSE;
	m_bAscendingRight = FALSE;

	m_ListLeft.SortItems(&CDlgForListCtrlMove::CompareItem, (DWORD_PTR)this);
	m_ListRight.SortItems(&CDlgForListCtrlMove::CompareItem, (DWORD_PTR)this);

	UpdateArrow(1);
	UpdateArrow(2);

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



// MARK: - CListCtrl 헤더 부 클릭 시 Sorting 함수에서 호출
int CALLBACK CDlgForListCtrlMove::CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CDlgForListCtrlMove* pDlg = (CDlgForListCtrlMove*)lParamSort;

	LVFINDINFO lvFind1, lvFind2;
	lvFind1.flags = LVFI_PARAM;
	lvFind1.lParam = lParam1;

	lvFind2.flags = LVFI_PARAM;
	lvFind2.lParam = lParam2;

	int nIndex1 = pDlg->m_ListLeft.FindItem(&lvFind1);
	int nIndex2 = pDlg->m_ListLeft.FindItem(&lvFind2);

	CString strText1 = pDlg->m_ListLeft.GetItemText(nIndex1, 0);
	CString strText2 = pDlg->m_ListLeft.GetItemText(nIndex2, 0);

	int nResult = 0;
	if (pDlg->m_bAscending) nResult = strText2.Compare(strText1);
	else nResult = strText1.Compare(strText2);

	return nResult;
}



void CDlgForListCtrlMove::UpdateArrow(int isLeft)
{
	// TODO: Add your implementation code here.
	CHeaderCtrl* pHeaderCtrl;
	if (isLeft == 1)
	{
		pHeaderCtrl = m_ListLeft.GetHeaderCtrl();
	}
	else
	{
		pHeaderCtrl = m_ListRight.GetHeaderCtrl();
	}

	HDITEM hdItem;
	TCHAR szBuffer[256];
	::ZeroMemory(&hdItem, sizeof(hdItem));
	::ZeroMemory(szBuffer, 256);

	hdItem.mask = -1;                           // ①
	hdItem.pszText = szBuffer;
	hdItem.cchTextMax = 256;

	pHeaderCtrl->GetItem(0, &hdItem);

	hdItem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);   // ②

	if (m_bAscending) hdItem.fmt |= HDF_SORTDOWN; // ③
	else hdItem.fmt |= HDF_SORTUP;

	pHeaderCtrl->SetItem(0, &hdItem);
}

void CDlgForListCtrlMove::OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	if (phdr->iItem == 0)
	{
		m_bAscending = !m_bAscending;
		UpdateArrow(1);
		m_ListLeft.SortItems(&CDlgForListCtrlMove::CompareItem, (DWORD_PTR)this);
	}
	*pResult = 0;
}


void CDlgForListCtrlMove::OnLvnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString ls_str = _T("");
	CEdit* pEdit = m_ListLeft.GetEditControl();
	pEdit->GetWindowTextW(ls_str);

	m_ListLeft.SetItemText(pDispInfo->item.iItem, 0, ls_str);

	*pResult = 0;
}

void CDlgForListCtrlMove::OnLvnEndlabeleditList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString ls_str = _T("");
	CEdit* pEdit = m_ListRight.GetEditControl();
	pEdit->GetWindowTextW(ls_str);

	m_ListRight.SetItemText(pDispInfo->item.iItem, 0, ls_str);

	*pResult = 0;
}

void CDlgForListCtrlMove::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	int li_status = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	switch (li_status)
	{
	case BST_CHECKED:
		m_ListLeft.SetView(LV_VIEW_SMALLICON);
		m_ListRight.SetView(LV_VIEW_SMALLICON);
		break;
	case BST_INDETERMINATE:
		m_ListLeft.SetView(LV_VIEW_ICON);
		m_ListRight.SetView(LV_VIEW_ICON);
		break;
	case BST_UNCHECKED:
		m_ListLeft.SetView(LVS_REPORT);
		m_ListRight.SetView(LVS_REPORT);
		break;
	default:
		break;
	}
}


void CDlgForListCtrlMove::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int nCnt = m_ListLeft.GetItemCount();
	for (int i = nCnt; i >= 0; i--) {
		if (m_ListLeft.GetCheck(i)) m_ListLeft.DeleteItem(i);
	}
}

// ⓐ
void CDlgForListCtrlMove::OnLvnBegindragList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	CPoint ptDrag, ptAction;
	m_nIndexLeftSel = pNMLV->iItem;
	if (m_nIndexLeftSel >= 0) {
		m_pImageListDrag = m_ListLeft.CreateDragImage(pNMLV->iItem, &ptDrag);
		m_pImageListDrag->SetBkColor(RGB(0, 0, 0));
		ptAction = pNMLV->ptAction;  // User clicked point

		SetCapture();
		m_pImageListDrag->BeginDrag(0, ptAction - ptDrag);
		m_ListLeft.ClientToScreen(&ptAction);
		m_pImageListDrag->DragEnter(NULL, ptAction);  // Show Drag Image 
												// NULL means that Drag image's owner is 바탕화면)
	}

	*pResult = 0;
}

// ⓑ
void CDlgForListCtrlMove::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pImageListDrag != NULL &&
		m_nIndexLeftSel >= 0)
	{
		ClientToScreen(&point);
		CWnd* pWnd = CWnd::WindowFromPoint(point);
		if (pWnd != NULL)
		{
			if (this == pWnd || IsChild(pWnd))
			{   // 대화상자 안 에서만 
				m_pImageListDrag->DragEnter(NULL, point);
				m_pImageListDrag->DragMove(point);
			}
			else
			{
				m_pImageListDrag->DragLeave(NULL);
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

// ⓒ
void CDlgForListCtrlMove::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString ls_str = _T("");

	if (m_pImageListDrag != NULL &&
		m_nIndexLeftSel >= 0)
	{
		ClientToScreen(&point);

		m_pImageListDrag->DragLeave(NULL);  // Eliminate drag image
		m_pImageListDrag->EndDrag();
		ReleaseCapture();

		// Add item into the right ListCtrl
		CWnd* pWnd = CWnd::WindowFromPoint(point);

		if (pWnd == &m_ListRight )
		{
			LVITEM lvItem;
			TCHAR szBuffer[256];
			::ZeroMemory(&lvItem, sizeof(lvItem));
			::ZeroMemory(szBuffer, sizeof(256));

			lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
			lvItem.iItem = m_nIndexLeftSel;
			lvItem.iImage = m_nIndexLeftSel;
			lvItem.pszText = szBuffer;
			lvItem.cchTextMax = 256;
			lvItem.iSubItem = 1;
			m_ListLeft.GetItem(&lvItem);

			LVFINDINFOW findInfo;
			findInfo.flags = LVFI_STRING;
			findInfo.psz = lvItem.pszText;

			if (m_ListRight.FindItem(&findInfo) != -1) {
				ls_str.Format(_T("[%s] is already exist"), lvItem.pszText);
				AfxMessageBox(ls_str);
			}
			else {
				m_ListRight.InsertItem(0, lvItem.pszText, lvItem.iImage);
				m_ListRight.SetItemText(0, 1, lvItem.pszText);
			}			
		}
		else
		{
			// 왼쪽 리스트컨트롤 이면 구체적인 아이템 인덱스 출력
			m_ListLeft.ScreenToClient(&point);
			int nIndex = m_ListLeft.HitTest(point);
			if (nIndex >= 0)
			{
				ls_str.Format(_T("Drop on [%d]th item"), nIndex);
				AfxMessageBox(ls_str);
			}
			else {
				ls_str.Format(_T("Drop on [%d]th item"), nIndex);
				AfxMessageBox(ls_str);
			}
		}

		delete m_pImageListDrag;
		m_pImageListDrag = NULL;
		m_nIndexLeftSel = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgForListCtrlMove::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//m_Avi.Play(0, -1, -1);
}


void CDlgForListCtrlMove::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//m_Avi.Stop();
}
