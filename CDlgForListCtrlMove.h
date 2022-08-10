#pragma once
#include "afxdialogex.h"

#define IMAGES_CNT 7

// CDlgForListCtrlMove dialog

class CDlgForListCtrlMove : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForListCtrlMove)

public:
	CDlgForListCtrlMove(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgForListCtrlMove();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FOR_LISTCTL_02 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	HICON hIcon;

	CListCtrl m_ListLeft;
	CListCtrl m_ListRight;
	BOOL m_bAscending, m_bAscendingRight;

	CImageList m_ImageListForNormal;
	CImageList m_ImageListForSmall;

	CImageList* m_pImageListDrag;
	CButton m_CheckStatus;
	CButton m_btn;

	CPoint m_point;

	int m_nIndexLeftSel;
	virtual BOOL OnInitDialog();

	static int CALLBACK CompareItem(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void UpdateArrow(int isLeft);

	afx_msg void OnLvnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnEndlabeleditList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnBegindragList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CAnimateCtrl m_Avi;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
