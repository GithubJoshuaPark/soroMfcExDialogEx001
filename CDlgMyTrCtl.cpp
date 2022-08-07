// CDlgMyTrCtl.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "afxdialogex.h"
#include "CDlgMyTrCtl.h"
#include <atlimage.h> // for CImage


// CDlgMyTrCtl dialog

IMPLEMENT_DYNAMIC(CDlgMyTrCtl, CDialogEx)

CDlgMyTrCtl::CDlgMyTrCtl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FOR_TREECTL, pParent)
{
	m_ImageListForTreeNode.Create(16, 16, ILC_COLOR24, IMAGES_CNT_FOR_TREE_NODE, 1);
}

CDlgMyTrCtl::~CDlgMyTrCtl()
{
}

void CDlgMyTrCtl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}


BEGIN_MESSAGE_MAP(CDlgMyTrCtl, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDlgMyTrCtl::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMyTrCtl::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgMyTrCtl message handlers


BOOL CDlgMyTrCtl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (int i = 0; i < IMAGES_CNT_FOR_TREE_NODE; i++) {
		m_ImageListForTreeNode.Add(AfxGetApp()->LoadIconW(IDI_ICON1 + i));
	}

	m_Tree.SetImageList(&m_ImageListForTreeNode, TVSIL_NORMAL);

	HTREEITEM hItem = NULL;
	hItem = m_Tree.InsertItem(_T("바탕화면"), 0, 0, TVI_ROOT);
		hItem = m_Tree.InsertItem(_T("내 문서"), 1, 5, hItem);
					m_Tree.InsertItem(_T("내 그림"), 2, 5, hItem);
					m_Tree.InsertItem(_T("내 비디오"), 3, 5, hItem);

			hItem = m_Tree.InsertItem(_T("Sample Folder"), 4, 5, hItem);
					hItem = m_Tree.InsertItem(_T("Sub Folder"), 4, 5, hItem);


	m_Tree.EnsureVisible(hItem);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgMyTrCtl::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CString ls_str = m_Tree.GetItemText(pNMTreeView->itemNew.hItem);
	GetDlgItem(IDC_STATIC)->SetWindowTextW(ls_str);
	*pResult = 0;
}


void CDlgMyTrCtl::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_Tree.GetRootItem();
	if (m_Tree.GetCheck(hItem))
		AfxMessageBox(m_Tree.GetItemText(hItem));

	CheckupChild(m_Tree.GetRootItem());
}

void CDlgMyTrCtl::CheckupChild(HTREEITEM hItem)
{
	HTREEITEM hChildItem = m_Tree.GetChildItem(hItem);

	while (hChildItem != NULL)
	{
		if (m_Tree.GetCheck(hChildItem))
			AfxMessageBox(m_Tree.GetItemText(hChildItem));

		// child item 
		if (m_Tree.ItemHasChildren(hChildItem))
			CheckupChild(hChildItem);

		hChildItem = m_Tree.GetNextItem(hChildItem, TVGN_NEXT);
	}
}