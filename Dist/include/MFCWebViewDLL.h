// MFCWebViewDLL.h - Main DLL header file
// This header contains the exported API for the MFC WebView DLL

#pragma once

#ifdef MFCWEBVIEWDLL_EXPORTS
#define MFCWEBVIEWDLL_API __declspec(dllexport)
#else
#define MFCWEBVIEWDLL_API __declspec(dllimport)
#endif

// Forward declaration
class CWebViewDialog;

// Exported C++ class
class MFCWEBVIEWDLL_API CMFCWebViewDLLApp : public CWinApp
{
public:
    CMFCWebViewDLLApp();
    virtual ~CMFCWebViewDLLApp();

    virtual BOOL InitInstance();
    virtual int ExitInstance();

    DECLARE_MESSAGE_MAP()
};

// Exported C functions for easy access from other applications
extern "C" {
    // Shows the WebView dialog with the default URL (google.com)
    MFCWEBVIEWDLL_API void ShowWebViewDialog();
    
    // Shows the WebView dialog with a custom URL
    MFCWEBVIEWDLL_API void ShowWebViewDialogWithURL(LPCTSTR lpszURL);
    
    // Gets the version of the DLL
    MFCWEBVIEWDLL_API LPCTSTR GetDLLVersion();
}
