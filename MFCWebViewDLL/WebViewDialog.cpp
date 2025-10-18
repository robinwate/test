// WebViewDialog.cpp - Implementation of the WebView Dialog

#include "pch.h"
#include "framework.h"
#include "WebViewDialog.h"
#include "MFCWebViewDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWebViewDialog dialog

IMPLEMENT_DYNAMIC(CWebViewDialog, CDialogEx)

CWebViewDialog::CWebViewDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_WEBVIEW_DIALOG, pParent)
    , m_strURL(_T("https://www.google.com"))
{
}

CWebViewDialog::~CWebViewDialog()
{
}

void CWebViewDialog::SetURL(LPCTSTR lpszURL)
{
    if (lpszURL != nullptr && _tcslen(lpszURL) > 0)
    {
        m_strURL = lpszURL;
    }
}

void CWebViewDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_WEBVIEW_PLACEHOLDER, m_webViewPlaceholder);
}

BEGIN_MESSAGE_MAP(CWebViewDialog, CDialogEx)
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CWebViewDialog message handlers

BOOL CWebViewDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set dialog title
    SetWindowText(_T("MFC WebView Dialog"));

    // Navigate to URL
    NavigateToURL();

    return TRUE;
}

void CWebViewDialog::NavigateToURL()
{
    // Get the placeholder control rectangle
    CRect rect;
    m_webViewPlaceholder.GetWindowRect(&rect);
    ScreenToClient(&rect);

    // Create a static text control to display the URL
    // Note: In a real implementation, you would use WebView2 or CHtmlView
    // For simplicity, we're showing the URL as text
    CString strMessage;
    strMessage.Format(_T("WebView loaded:\n\n%s\n\nNote: To implement actual web browsing,\nintegrate Microsoft Edge WebView2 control.\n\nThis is a placeholder implementation."), m_strURL);
    m_webViewPlaceholder.SetWindowText(strMessage);
    
    // Center the text
    DWORD dwStyle = m_webViewPlaceholder.GetStyle();
    m_webViewPlaceholder.ModifyStyle(0, SS_CENTER);
}

void CWebViewDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // Resize the web view placeholder to fill the dialog
    if (m_webViewPlaceholder.GetSafeHwnd())
    {
        CRect rect;
        GetClientRect(&rect);
        rect.DeflateRect(10, 10);
        m_webViewPlaceholder.MoveWindow(&rect);
    }
}
