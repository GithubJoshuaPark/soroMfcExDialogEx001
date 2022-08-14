#pragma once
#include "afxdialogex.h"

#define IMAGES_CNT 7

// CDlgForListCtrl dialog

class CDlgForListCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForListCtrl)
private:
	
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
	BOOL m_bAscending;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();

	afx_msg void OnLvnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void UpdateArrow();
	afx_msg void OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
