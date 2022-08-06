
// soroMfcExDialogEx001View.h : interface of the CsoroMfcExDialogEx001View class
//

#pragma once

#include "CDlgForListCtrl.h"
#include "CDlgHasUserClass.h"

#define ID_BTN01 1234
#define ID_BTN02 1235

class CsoroMfcExDialogEx001View : public CView
{
protected: // create from serialization only
	CsoroMfcExDialogEx001View() noexcept;
	DECLARE_DYNCREATE(CsoroMfcExDialogEx001View)

// Attributes
public:
	CsoroMfcExDialogEx001Doc* GetDocument() const;

// Operations
public:
	CButton m_btn;
	CButton m_btn2;
	CDlgForListCtrl m_CDlgForListCtrl;
	CDlgHasUserClass m_CDlgHasUserClass;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CsoroMfcExDialogEx001View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	void BtnClick();
	void Btn2Click();
};

#ifndef _DEBUG  // debug version in soroMfcExDialogEx001View.cpp
inline CsoroMfcExDialogEx001Doc* CsoroMfcExDialogEx001View::GetDocument() const
   { return reinterpret_cast<CsoroMfcExDialogEx001Doc*>(m_pDocument); }
#endif

