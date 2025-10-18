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
    ON_WM_DESTROY()
END_MESSAGE_MAP()

// CWebViewDialog message handlers

BOOL CWebViewDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set dialog title
    SetWindowText(_T("MFC WebView Dialog"));

    // Initialize WebView2
    InitializeWebView();

    return TRUE;
}

void CWebViewDialog::InitializeWebView()
{
    // Get the placeholder control rectangle
    CRect rect;
    m_webViewPlaceholder.GetWindowRect(&rect);
    ScreenToClient(&rect);

    // Hide the placeholder control
    m_webViewPlaceholder.ShowWindow(SW_HIDE);

    // Create WebView2 environment and controller
    CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this, rect](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                if (FAILED(result))
                {
                    AfxMessageBox(_T("Failed to create WebView2 environment.\n\nPlease ensure Microsoft Edge WebView2 Runtime is installed."), MB_ICONERROR);
                    return result;
                }

                // Create a CoreWebView2Controller
                env->CreateCoreWebView2Controller(m_hWnd,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [this, rect](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (FAILED(result))
                            {
                                AfxMessageBox(_T("Failed to create WebView2 controller."), MB_ICONERROR);
                                return result;
                            }

                            if (controller != nullptr)
                            {
                                m_webViewController = controller;
                                m_webViewController->get_CoreWebView2(&m_webView);
                            }

                            // Resize WebView to fit the dialog
                            if (m_webViewController)
                            {
                                RECT bounds = { rect.left, rect.top, rect.right, rect.bottom };
                                m_webViewController->put_Bounds(bounds);
                            }

                            // Navigate to the URL
                            NavigateToURL();

                            return S_OK;
                        }).Get());

                return S_OK;
            }).Get());
}

void CWebViewDialog::NavigateToURL()
{
    if (m_webView)
    {
        // Convert CString to wide string
        CStringW wideURL(m_strURL);
        m_webView->Navigate(wideURL.GetString());
    }
}

void CWebViewDialog::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    // Resize the WebView2 control to fill the dialog
    if (m_webViewController)
    {
        CRect rect;
        GetClientRect(&rect);
        rect.DeflateRect(10, 40, 10, 50); // Leave space for OK/Cancel buttons

        RECT bounds = { rect.left, rect.top, rect.right, rect.bottom };
        m_webViewController->put_Bounds(bounds);
    }
}

void CWebViewDialog::OnDestroy()
{
    // Clean up WebView2
    if (m_webViewController)
    {
        m_webViewController->Close();
        m_webViewController = nullptr;
    }
    m_webView = nullptr;

    CDialogEx::OnDestroy();
}
