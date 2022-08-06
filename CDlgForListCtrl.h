#pragma once
#include "afxdialogex.h"

#define IMAGES_CNT 7

// CDlgForListCtrl dialog

class CDlgForListCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForListCtrl)

public:
	CDlgForListCtrl(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgForListCtrl();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CImageList m_ImageListForNormal;
	CImageList m_ImageListForSmall;
	CListCtrl m_List;
	CButton m_CheckStatus;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
};