// dllmain.cpp : Defines the initialization routines for the DLL.

#include "pch.h"
#include "framework.h"
#include "MFCWebViewDLL.h"
#include "WebViewDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCWebViewDLLApp

BEGIN_MESSAGE_MAP(CMFCWebViewDLLApp, CWinApp)
END_MESSAGE_MAP()

// CMFCWebViewDLLApp construction

CMFCWebViewDLLApp::CMFCWebViewDLLApp()
{
}

CMFCWebViewDLLApp::~CMFCWebViewDLLApp()
{
}

// The one and only CMFCWebViewDLLApp object

CMFCWebViewDLLApp theApp;

// CMFCWebViewDLLApp initialization

BOOL CMFCWebViewDLLApp::InitInstance()
{
    CWinApp::InitInstance();

    return TRUE;
}

int CMFCWebViewDLLApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}

// Exported C functions implementation

extern "C" MFCWEBVIEWDLL_API void ShowWebViewDialog()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    CWebViewDialog dlg;
    dlg.DoModal();
}

extern "C" MFCWEBVIEWDLL_API void ShowWebViewDialogWithURL(LPCTSTR lpszURL)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    CWebViewDialog dlg;
    dlg.SetURL(lpszURL);
    dlg.DoModal();
}

extern "C" MFCWEBVIEWDLL_API LPCTSTR GetDLLVersion()
{
    return _T("1.0.0");
}
