
// soroMfcExDialogEx001View.h : interface of the CsoroMfcExDialogEx001View class
//

#pragma once

#include "CDlgForListCtrl.h"
#include "CDlgHasUserClass.h"
#include "CListCtrlUsingSysImages.h"
#include "CDlgMyTrCtl.h"
#include "CDlgForListCtrlMove.h"
#include "CUserData.h"
#include "CBufferDC.h"

#define ID_BTN01 12345
#define ID_BTN02 12346
#define ID_BTN03 12347
#define ID_BTN04 12348
#define ID_BTN05 12349
#define ID_CHECK_BTN01 12399

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
	CButton m_check;  // for enable/disable m_btn

	CButton m_btn;
	CButton m_btn2;
	CButton m_btn3;
	CButton m_btn4;
	CButton m_btn5;
	

	CDlgForListCtrl m_CDlgForListCtrl;
	CDlgHasUserClass m_CDlgHasUserClass;
	CListCtrlUsingSysImages m_CListCtrlUsingSysImages;
	CDlgMyTrCtl m_CDlgMyTrCtl;
	CDlgForListCtrlMove m_CDlgForListCtrlMove;

	CUserData m_CUserData;


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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
private:
	void BtnClick();
	void Btn2Click();
	void Btn3Click();
	void Btn4Click();
	void Btn5Click();
	void BtnChecked();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in soroMfcExDialogEx001View.cpp
inline CsoroMfcExDialogEx001Doc* CsoroMfcExDialogEx001View::GetDocument() const
   { return reinterpret_cast<CsoroMfcExDialogEx001Doc*>(m_pDocument); }
#endif

