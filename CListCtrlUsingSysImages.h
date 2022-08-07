#pragma once
#include "afxdialogex.h"


// CListCtrlUsingSysImages dialog

class CListCtrlUsingSysImages : public CDialogEx
{
	DECLARE_DYNAMIC(CListCtrlUsingSysImages)

public:
	CListCtrlUsingSysImages(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CListCtrlUsingSysImages();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FOR_LISTCTL_SYS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	void SetSysImageOnMyList();
	int GetIconIndexFromFile(CString strFilePath);
	void AddItemOnMyList();
	BOOL m_isChecked;
	afx_msg void OnBnClickedCheck1();
};

