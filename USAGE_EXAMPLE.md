# Usage Example - MFC WebView DLL

This document provides a complete working example of how to use the MFCWebViewDLL in your MFC application.

## Example 1: Simple Console-Style MFC App

This example shows the minimal code needed to use the DLL.

### Step 1: Project Setup in Visual Studio

1. Create a new MFC Application project
2. Configure the project to use MFC in a shared DLL
3. Add the include directory: `Dist\include`
4. Add the library directory: `Dist\lib\x64` (or x86)
5. Add to Additional Dependencies: `MFCWebViewDLL.lib`

### Step 2: Add Code to Your Application

**In your main dialog or view class header (e.g., MyAppDlg.h):**

```cpp
#pragma once

#include "afxdialogex.h"
#include "MFCWebViewDLL.h"  // Add this line

class CMyAppDlg : public CDialogEx
{
public:
    CMyAppDlg(CWnd* pParent = nullptr);

    // ... other declarations ...

protected:
    afx_msg void OnBnClickedButtonShowWeb();
    DECLARE_MESSAGE_MAP()
};
```

**In your implementation file (e.g., MyAppDlg.cpp):**

```cpp
#include "pch.h"
#include "MyAppDlg.h"

BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_SHOW_WEB, &CMyAppDlg::OnBnClickedButtonShowWeb)
END_MESSAGE_MAP()

void CMyAppDlg::OnBnClickedButtonShowWeb()
{
    // Simple one-liner to show the WebView dialog
    ShowWebViewDialog();
}
```

## Example 2: Custom URL

Show a specific website:

```cpp
void CMyAppDlg::OnBnClickedButtonShowMicrosoft()
{
    ShowWebViewDialogWithURL(_T("https://www.microsoft.com"));
}

void CMyAppDlg::OnBnClickedButtonShowGitHub()
{
    ShowWebViewDialogWithURL(_T("https://www.github.com"));
}

void CMyAppDlg::OnBnClickedButtonShowCustom()
{
    CString url = _T("https://www.cppreference.com");
    ShowWebViewDialogWithURL(url);
}
```

## Example 3: Using the Dialog Class Directly

For more control over the dialog:

```cpp
#include "MFCWebViewDLL.h"
#include "WebViewDialog.h"  // Add this for direct class access

void CMyAppDlg::OnBnClickedButtonAdvanced()
{
    CWebViewDialog dlg;
    
    // Set custom URL before showing
    dlg.SetURL(_T("https://www.stackoverflow.com"));
    
    // Show the dialog and check result
    INT_PTR result = dlg.DoModal();
    
    if (result == IDOK)
    {
        AfxMessageBox(_T("User clicked OK"));
    }
    else if (result == IDCANCEL)
    {
        AfxMessageBox(_T("User clicked Cancel"));
    }
}
```

## Example 4: Dynamic URL from User Input

Get URL from an edit control:

```cpp
void CMyAppDlg::OnBnClickedButtonGo()
{
    CString strURL;
    
    // Get URL from edit control (IDC_EDIT_URL)
    GetDlgItemText(IDC_EDIT_URL, strURL);
    
    // Validate URL is not empty
    if (strURL.IsEmpty())
    {
        AfxMessageBox(_T("Please enter a URL"));
        return;
    }
    
    // Add protocol if missing
    if (strURL.Find(_T("http://")) != 0 && strURL.Find(_T("https://")) != 0)
    {
        strURL = _T("https://") + strURL;
    }
    
    // Show dialog with user's URL
    ShowWebViewDialogWithURL(strURL);
}
```

## Example 5: Menu Integration

Add to your menu handler:

**Resource.h:**
```cpp
#define ID_FILE_SHOWWEBVIEW     32771
#define ID_FILE_SHOWGOOGLE      32772
#define ID_FILE_SHOWMICROSOFT   32773
```

**Menu Resource (.rc file):**
```
MENUITEM "Show WebView\tCtrl+W", ID_FILE_SHOWWEBVIEW
MENUITEM "Open Google", ID_FILE_SHOWGOOGLE
MENUITEM "Open Microsoft", ID_FILE_SHOWMICROSOFT
```

**Message Map:**
```cpp
BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
    ON_COMMAND(ID_FILE_SHOWWEBVIEW, &CMyAppDlg::OnFileShowWebView)
    ON_COMMAND(ID_FILE_SHOWGOOGLE, &CMyAppDlg::OnFileShowGoogle)
    ON_COMMAND(ID_FILE_SHOWMICROSOFT, &CMyAppDlg::OnFileShowMicrosoft)
END_MESSAGE_MAP()
```

**Handlers:**
```cpp
void CMyAppDlg::OnFileShowWebView()
{
    ShowWebViewDialog();
}

void CMyAppDlg::OnFileShowGoogle()
{
    ShowWebViewDialogWithURL(_T("https://www.google.com"));
}

void CMyAppDlg::OnFileShowMicrosoft()
{
    ShowWebViewDialogWithURL(_T("https://www.microsoft.com"));
}
```

## Example 6: Version Check

Display the DLL version:

```cpp
void CMyAppDlg::OnBnClickedButtonVersion()
{
    LPCTSTR version = GetDLLVersion();
    
    CString msg;
    msg.Format(_T("MFC WebView DLL Version: %s"), version);
    
    AfxMessageBox(msg);
}
```

## Example 7: Error Handling

Proper error handling when loading the DLL:

```cpp
void CMyAppDlg::OnBnClickedButtonShowWebSafe()
{
    try
    {
        // Try to call the DLL function
        ShowWebViewDialog();
    }
    catch (...)
    {
        AfxMessageBox(_T("Error: Could not load MFC WebView DLL.\n\n")
                      _T("Please ensure:\n")
                      _T("1. MFCWebViewDLL.dll is in the application directory\n")
                      _T("2. All required MFC DLLs are available\n")
                      _T("3. The correct architecture (x86/x64) is being used"),
                      MB_ICONERROR);
    }
}
```

## Complete Mini Application Example

Here's a complete minimal MFC dialog application:

**MyTestApp.h:**
```cpp
#pragma once

#include "afxdialogex.h"
#include "resource.h"
#include "MFCWebViewDLL.h"

class CMyTestAppDlg : public CDialogEx
{
public:
    CMyTestAppDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_MYTESTAPP_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    afx_msg void OnBnClickedButtonShow();
    afx_msg void OnBnClickedButtonCustom();
    
    DECLARE_MESSAGE_MAP()

private:
    CEdit m_editURL;
};
```

**MyTestApp.cpp:**
```cpp
#include "pch.h"
#include "MyTestApp.h"

BEGIN_MESSAGE_MAP(CMyTestAppDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_SHOW, &CMyTestAppDlg::OnBnClickedButtonShow)
    ON_BN_CLICKED(IDC_BUTTON_CUSTOM, &CMyTestAppDlg::OnBnClickedButtonCustom)
END_MESSAGE_MAP()

CMyTestAppDlg::CMyTestAppDlg(CWnd* pParent)
    : CDialogEx(IDD_MYTESTAPP_DIALOG, pParent)
{
}

void CMyTestAppDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_URL, m_editURL);
}

BOOL CMyTestAppDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    // Set default URL
    m_editURL.SetWindowText(_T("https://www.google.com"));
    
    return TRUE;
}

void CMyTestAppDlg::OnBnClickedButtonShow()
{
    // Show with default URL
    ShowWebViewDialog();
}

void CMyTestAppDlg::OnBnClickedButtonCustom()
{
    // Get URL from edit control
    CString url;
    m_editURL.GetWindowText(url);
    
    if (!url.IsEmpty())
    {
        ShowWebViewDialogWithURL(url);
    }
}
```

## Deployment Checklist

When deploying your application that uses MFCWebViewDLL:

- [ ] Copy `MFCWebViewDLL.dll` to your application's directory
- [ ] Ensure MFC runtime DLLs are available:
  - `mfc140u.dll` (or appropriate version)
  - `msvcp140.dll`
  - `vcruntime140.dll`
- [ ] Use the same architecture (x86 or x64) for both DLL and application
- [ ] Test on a clean machine without Visual Studio installed

## Common Issues

### Issue: "The program can't start because MFCWebViewDLL.dll is missing"

**Solution:**
- Copy the DLL to the same directory as your .exe
- Or add the DLL location to the system PATH

### Issue: Linker error LNK2019 (unresolved external symbol)

**Solution:**
- Ensure `MFCWebViewDLL.lib` is in the Additional Dependencies
- Verify the library directory is correctly set
- Check that you're linking against the correct architecture

### Issue: Access violation or crash when calling DLL functions

**Solution:**
- Verify architecture match (x86 vs x64)
- Ensure both application and DLL use MFC in a Shared DLL
- Check that all required MFC DLLs are present

## Additional Resources

- See `Dist\README.md` for complete API documentation
- See `BUILD_INSTRUCTIONS.md` for building the DLL
- See main `README.md` for project overview

---

Happy coding!
