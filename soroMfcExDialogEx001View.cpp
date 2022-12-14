
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
	ON_COMMAND(ID_BTN03, &CsoroMfcExDialogEx001View::Btn3Click)
	ON_COMMAND(ID_BTN04, &CsoroMfcExDialogEx001View::Btn4Click)
	ON_COMMAND(ID_BTN05, &CsoroMfcExDialogEx001View::Btn5Click)
	ON_COMMAND(ID_CHECK_BTN01, &CsoroMfcExDialogEx001View::BtnChecked)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
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
int CsoroMfcExDialogEx001View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	HICON hIcon[] = {
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR),
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR),
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR),
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR),
		(HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON5), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR)
	};

	m_check.Create(_T("Enable/Disable"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		CRect(150, 40, 300, 80),
		this,
		ID_CHECK_BTN01);

	m_btn.Create(_T("CDlgForListCtrl"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(150, 80, 300, 150),
		this,
		ID_BTN01);
	m_btn.SetIcon(hIcon[0]);

	m_btn2.Create(_T("CDlgHasUser"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(300, 80, 450, 150),
		this,
		ID_BTN02);
	m_btn2.SetIcon(hIcon[1]);

	m_btn3.Create(_T("CV Using SysImg"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(450, 80, 600, 150),
		this,
		ID_BTN03);
	m_btn3.SetIcon(hIcon[2]);

	m_btn4.Create(_T("CDlgMyTrCtl"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(600, 80, 750, 150),
		this,
		ID_BTN04);
	m_btn4.SetIcon(hIcon[3]);

	m_btn5.Create(_T("ListCtls"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
		CRect(750, 80, 900, 150),
		this,
		ID_BTN05);
	m_btn5.SetIcon(hIcon[4]);


	m_CUserData.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		CRect(150, 160, 300, 300) , this, M_CUSERDATA_ID);

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

void CsoroMfcExDialogEx001View::Btn3Click()
{
	// TODO: Add your implementation code here.
	//AfxMessageBox(_T("God will make a way"));

	m_CListCtrlUsingSysImages.DoModal();
}

void CsoroMfcExDialogEx001View::Btn4Click()
{
	// TODO: Add your implementation code here.
	//AfxMessageBox(_T("God will make a way"));

	m_CDlgMyTrCtl.DoModal();
}

void CsoroMfcExDialogEx001View::Btn5Click()
{
	// TODO: Add your implementation code here.
	//AfxMessageBox(_T("God will make a way"));

	m_CDlgForListCtrlMove.DoModal();
}

void CsoroMfcExDialogEx001View::BtnChecked()
{
	// TODO: Add your control notification handler code here
	int li_status = m_check.GetCheck();
	switch (li_status)
	{
	case BST_CHECKED:
		m_btn.EnableWindow(false);
		m_btn2.EnableWindow(false);
		m_btn3.EnableWindow(false);
		m_btn4.EnableWindow(false);
		m_btn5.EnableWindow(false);
		break;
	case BST_UNCHECKED:
		m_btn.EnableWindow(true);
		m_btn2.EnableWindow(true);
		m_btn3.EnableWindow(true);
		m_btn4.EnableWindow(true);
		m_btn5.EnableWindow(true);
		break;
	default:
		break;
	}
}

void CsoroMfcExDialogEx001View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//CBufferDC dc(this);

	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages

	CRect cRect;
	GetClientRect(&cRect);
	dc.FillSolidRect(&cRect, RGB(192, 0, 0));

	cRect -= CRect(7, 7, 7, 7);
	dc.SelectStockObject(NULL_PEN);
	dc.RoundRect(&cRect, CPoint(21, 21));

	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW(cRect.Width()/2, cRect.Height()/2, _T("Test String!"));
}


BOOL CsoroMfcExDialogEx001View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	
	//return TRUE;
	
	return CView::OnEraseBkgnd(pDC);
}
