
// soroMfcExDialogEx001.h : main header file for the soroMfcExDialogEx001 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CsoroMfcExDialogEx001App:
// See soroMfcExDialogEx001.cpp for the implementation of this class
//

class CsoroMfcExDialogEx001App : public CWinApp
{
public:
	CsoroMfcExDialogEx001App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CsoroMfcExDialogEx001App theApp;
