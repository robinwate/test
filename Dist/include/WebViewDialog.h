// WebViewDialog.h - WebView Dialog class header

#pragma once

#include "Resource.h"
#include <afxwin.h>

#ifdef MFCWEBVIEWDLL_EXPORTS
#define WEBVIEWDLG_API __declspec(dllexport)
#else
#define WEBVIEWDLG_API __declspec(dllimport)
#endif

// CWebViewDialog dialog - exported class that can be used directly by client apps
class WEBVIEWDLG_API CWebViewDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CWebViewDialog)

public:
    CWebViewDialog(CWnd* pParent = nullptr);
    virtual ~CWebViewDialog();

    // Set custom URL before showing dialog
    void SetURL(LPCTSTR lpszURL);

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_WEBVIEW_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    
    DECLARE_MESSAGE_MAP()

private:
    CString m_strURL;
    CStatic m_webViewPlaceholder;
    
    void NavigateToURL();
    
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};
