#pragma once
#include "afxdialogex.h"

#define IMAGES_CNT_FOR_TREE_NODE 7

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
public:
	CImageList m_ImageListForTreeNode;
	CTreeCtrl m_Tree;
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	void CheckupChild(HTREEITEM hItem);
};
