// CListCtrlUsingSysImages.cpp : implementation file
//

#include "pch.h"
#include "soroMfcExDialogEx001.h"
#include "afxdialogex.h"
#include "CListCtrlUsingSysImages.h"


// CListCtrlUsingSysImages dialog

IMPLEMENT_DYNAMIC(CListCtrlUsingSysImages, CDialogEx)

CListCtrlUsingSysImages::CListCtrlUsingSysImages(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FOR_LISTCTL_SYS, pParent)
	, m_isChecked(FALSE)
{

}

CListCtrlUsingSysImages::~CListCtrlUsingSysImages()
{
}

void CListCtrlUsingSysImages::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Check(pDX, IDC_CHECK1, m_isChecked);
}


BEGIN_MESSAGE_MAP(CListCtrlUsingSysImages, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CListCtrlUsingSysImages::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CListCtrlUsingSysImages message handlers


BOOL CListCtrlUsingSysImages::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 1. OS System 에서 사용하는 이미지를 m_List의 이미지로 사용하기 위해 셋팅
	SetSysImageOnMyList();

	// 2. 항목 추가
	AddItemOnMyList();



	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CListCtrlUsingSysImages::SetSysImageOnMyList()
{
	// TODO: Add your implementation code here.
	// TODO:  Add extra initialization here
	SHFILEINFO ShellInfo;
	::ZeroMemory(&ShellInfo, sizeof(ShellInfo));

	// 큰 아이콛
	HIMAGELIST hSysImage = reinterpret_cast<HIMAGELIST>(::SHGetFileInfo(
		_T("C:\\"), 0,
		&ShellInfo, sizeof(ShellInfo),
		SHGFI_LARGEICON | SHGFI_SYSICONINDEX));

	// 작은 아이콛
	::ZeroMemory(&ShellInfo, sizeof(ShellInfo));
	HIMAGELIST hSysImageSmall = reinterpret_cast<HIMAGELIST>(::SHGetFileInfo(
		_T("C:\\"), 0,
		&ShellInfo, sizeof(ShellInfo),
		SHGFI_SMALLICON | SHGFI_SYSICONINDEX));

	// 
	ListView_SetImageList(m_List.m_hWnd, hSysImage, LVSIL_NORMAL);
	ListView_SetImageList(m_List.m_hWnd, hSysImageSmall, LVSIL_SMALL);
}

int CListCtrlUsingSysImages::GetIconIndexFromFile(CString strFilePath)
{
	SHFILEINFO ShellInfo;
	::ZeroMemory(&ShellInfo, sizeof(ShellInfo));

	::SHGetFileInfo(strFilePath.GetBuffer(),
		0,
		&ShellInfo, sizeof(ShellInfo),
		SHGFI_LARGEICON | SHGFI_SYSICONINDEX );

	return ShellInfo.iIcon;
}

void CListCtrlUsingSysImages::AddItemOnMyList()
{
	CString ls_strItem = _T("C:\\");
	m_List.InsertItem(0, ls_strItem, GetIconIndexFromFile(ls_strItem));

	ls_strItem = _T("C:\\Windows");
	m_List.InsertItem(1, ls_strItem, GetIconIndexFromFile(ls_strItem));

	ls_strItem = _T("C:\\Windows\\notepad.exe");
	m_List.InsertItem(2, ls_strItem, GetIconIndexFromFile(ls_strItem));

	ls_strItem = _T("C:\\Windows\\explorer.exe");
	m_List.InsertItem(3, ls_strItem, GetIconIndexFromFile(ls_strItem));
}

void CListCtrlUsingSysImages::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (m_isChecked) {
		m_List.SetView(LV_VIEW_ICON);
	}
	else {
		m_List.SetView(LV_VIEW_SMALLICON);
	}
}
