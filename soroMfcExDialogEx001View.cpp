
// soroMfcExDialogEx001View.cpp : implementation of the CsoroMfcExDialogEx001View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "soroMfcExDialogEx001.h"
#endif

#include "soroMfcExDialogEx001Doc.h"
#include "soroMfcExDialogEx001View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsoroMfcExDialogEx001View

IMPLEMENT_DYNCREATE(CsoroMfcExDialogEx001View, CView)

BEGIN_MESSAGE_MAP(CsoroMfcExDialogEx001View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_COMMAND(ID_BTN01, &CsoroMfcExDialogEx001View::BtnClick)
	ON_COMMAND(ID_BTN02, &CsoroMfcExDialogEx001View::Btn2Click)
	ON_COMMAND(ID_CHECK_BTN01, &CsoroMfcExDialogEx001View::BtnChecked)
END_MESSAGE_MAP()

// CsoroMfcExDialogEx001View construction/destruction

CsoroMfcExDialogEx001View::CsoroMfcExDialogEx001View() noexcept
{
	// TODO: add construction code here


}

CsoroMfcExDialogEx001View::~CsoroMfcExDialogEx001View()
{
}

BOOL CsoroMfcExDialogEx001View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CsoroMfcExDialogEx001View drawing

void CsoroMfcExDialogEx001View::OnDraw(CDC* /*pDC*/)
{
	CsoroMfcExDialogEx001Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CsoroMfcExDialogEx001View printing

BOOL CsoroMfcExDialogEx001View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CsoroMfcExDialogEx001View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CsoroMfcExDialogEx001View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CsoroMfcExDialogEx001View diagnostics

#ifdef _DEBUG
void CsoroMfcExDialogEx001View::AssertValid() const
{
	CView::AssertValid();
}

void CsoroMfcExDialogEx001View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsoroMfcExDialogEx001Doc* CsoroMfcExDialogEx001View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsoroMfcExDialogEx001Doc)));
	return (CsoroMfcExDialogEx001Doc*)m_pDocument;
}
#endif //_DEBUG


// CsoroMfcExDialogEx001View message handlers


BOOL CsoroMfcExDialogEx001View::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class


	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int CsoroMfcExDialogEx001View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	HICON hIcon[] = {
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR),
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR)
	};

	m_btn.Create(_T("CDlgForListCtrl"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(150, 40, 300, 150),
		this,
		ID_BTN01);
	m_btn.SetIcon(hIcon[0]);

	m_check.Create(_T("Enable/Disable"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		CRect(150, 160, 300, 200),
		this,
		ID_CHECK_BTN01);

	m_btn2.Create(_T("CDlgHasUser"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(300, 40, 450, 150),
		this,
		ID_BTN02);
	m_btn2.SetIcon(hIcon[1]);

	return 0;
}


void CsoroMfcExDialogEx001View::BtnClick()
{
	// TODO: Add your implementation code here.
	//AfxMessageBox(_T("God will make a way"));

	m_CDlgForListCtrl.DoModal();
}

void CsoroMfcExDialogEx001View::Btn2Click()
{
	// TODO: Add your implementation code here.
	//AfxMessageBox(_T("God will make a way"));

	m_CDlgHasUserClass.DoModal();
}

void CsoroMfcExDialogEx001View::BtnChecked()
{
	// TODO: Add your control notification handler code here
	int li_status = m_check.GetCheck();
	switch (li_status)
	{
	case BST_CHECKED:
		m_btn.EnableWindow(false);
		break;
	case BST_UNCHECKED:
		m_btn.EnableWindow(true);
		break;
	default:
		break;
	}
}