# MFC WebView DLL - API Documentation

## Overview
The MFC WebView DLL provides a simple way to display web content in a dialog from any MFC application. This DLL uses Microsoft Edge WebView2 for actual web browsing and can be easily integrated into your MFC projects.

## Version
Current Version: 1.0.0

## Features
- Easy-to-use C-style exported functions
- Exported C++ class for advanced usage
- Pre-configured dialog with Microsoft Edge WebView2 control
- Actual web browsing capability
- Support for custom URLs
- Compatible with both x86 and x64 platforms

## Distribution Contents

The `Dist` folder contains everything needed to use this DLL:

```
Dist/
├── include/           # Header files
│   ├── MFCWebViewDLL.h
│   └── WebViewDialog.h
├── lib/
│   ├── x86/          # 32-bit import libraries (generated after build)
│   └── x64/          # 64-bit import libraries (generated after build)
└── dll/
    ├── x86/          # 32-bit DLLs (generated after build)
    └── x64/          # 64-bit DLLs (generated after build)
```

## Building the DLL

### Prerequisites
- Visual Studio 2022 (or later) with C++ and MFC support
- Windows 10 SDK
- Microsoft Edge WebView2 Runtime (automatically installed on Windows 11)

### Build Instructions

1. Open `MFCWebViewDLL.sln` in Visual Studio
2. Restore NuGet packages (right-click solution > Restore NuGet Packages)
3. Select your desired configuration:
   - Debug|Win32 (32-bit debug)
   - Release|Win32 (32-bit release)
   - Debug|x64 (64-bit debug)
   - Release|x64 (64-bit release)
4. Build the solution (Build > Build Solution or Ctrl+Shift+B)
5. After building, copy the generated files:
   - Copy `*.dll` to `Dist/dll/x86/` or `Dist/dll/x64/`
   - Copy `*.lib` to `Dist/lib/x86/` or `Dist/lib/x64/`

## Integration Guide

### Option 1: Using C-Style Functions (Recommended for Simple Cases)

This is the easiest way to use the DLL.

#### Step 1: Add to Your Project

1. Copy the `Dist` folder to your project directory
2. In Visual Studio, add the include directory:
   - Project Properties > C/C++ > General > Additional Include Directories
   - Add: `$(ProjectDir)Dist\include`

3. Add the library directory:
   - Project Properties > Linker > General > Additional Library Directories
   - For x86: Add `$(ProjectDir)Dist\lib\x86`
   - For x64: Add `$(ProjectDir)Dist\lib\x64`

4. Link the library:
   - Project Properties > Linker > Input > Additional Dependencies
   - Add: `MFCWebViewDLL.lib`

5. Ensure the DLL is accessible at runtime:
   - Copy the appropriate DLL from `Dist/dll/x86` or `Dist/dll/x64` to your output directory
   - Or add the DLL directory to your PATH

#### Step 2: Include the Header

```cpp
#include "MFCWebViewDLL.h"
```

#### Step 3: Call the Functions

```cpp
// Show dialog with default URL (google.com)
ShowWebViewDialog();

// Show dialog with custom URL
ShowWebViewDialogWithURL(_T("https://www.microsoft.com"));

// Get DLL version
LPCTSTR version = GetDLLVersion();
```

### Option 2: Using C++ Class (Advanced)

Use this approach for more control over the dialog.

#### Step 1-2: Same as Option 1

#### Step 3: Include Headers

```cpp
#include "MFCWebViewDLL.h"
#include "WebViewDialog.h"
```

#### Step 4: Use the Dialog Class

```cpp
// Create and show the dialog
CWebViewDialog dlg;
dlg.SetURL(_T("https://www.example.com"));
INT_PTR result = dlg.DoModal();

if (result == IDOK)
{
    // User clicked OK
}
```

## API Reference

### C Functions

#### ShowWebViewDialog()
```cpp
void ShowWebViewDialog();
```
Displays the WebView dialog with the default URL (https://www.google.com).

**Parameters:** None

**Returns:** void

**Example:**
```cpp
ShowWebViewDialog();
```

---

#### ShowWebViewDialogWithURL()
```cpp
void ShowWebViewDialogWithURL(LPCTSTR lpszURL);
```
Displays the WebView dialog with a custom URL.

**Parameters:**
- `lpszURL`: Pointer to a null-terminated string containing the URL

**Returns:** void

**Example:**
```cpp
ShowWebViewDialogWithURL(_T("https://www.bing.com"));
```

---

#### GetDLLVersion()
```cpp
LPCTSTR GetDLLVersion();
```
Returns the version string of the DLL.

**Parameters:** None

**Returns:** Pointer to a null-terminated string containing the version

**Example:**
```cpp
LPCTSTR version = GetDLLVersion();
AfxMessageBox(version); // Shows "1.0.0"
```

### C++ Classes

#### CWebViewDialog

A modal dialog class that displays web content.

##### Public Methods

**Constructor**
```cpp
CWebViewDialog(CWnd* pParent = nullptr);
```
Creates a new instance of the dialog.

**SetURL**
```cpp
void SetURL(LPCTSTR lpszURL);
```
Sets the URL to display in the dialog. Must be called before `DoModal()`.

**DoModal**
```cpp
INT_PTR DoModal();
```
Displays the dialog modally. Returns IDOK or IDCANCEL.

##### Usage Example
```cpp
CWebViewDialog dlg;
dlg.SetURL(_T("https://www.github.com"));
if (dlg.DoModal() == IDOK)
{
    // Process OK
}
```

## Sample Application Code

Here's a complete example of a simple MFC application that uses the DLL:

```cpp
// In your MFC app's command handler:

void CMyApp::OnShowWebView()
{
    // Method 1: Simple function call
    ShowWebViewDialog();
}

void CMyApp::OnShowCustomWebView()
{
    // Method 2: Function call with custom URL
    ShowWebViewDialogWithURL(_T("https://www.stackoverflow.com"));
}

void CMyApp::OnShowWebViewAdvanced()
{
    // Method 3: Using the class directly
    CWebViewDialog dlg;
    dlg.SetURL(_T("https://www.cplusplus.com"));
    
    if (dlg.DoModal() == IDOK)
    {
        AfxMessageBox(_T("Dialog closed with OK"));
    }
}
```

## Deployment Checklist

When distributing your application that uses this DLL:

- [ ] Include the appropriate MFCWebViewDLL.dll (x86 or x64)
- [ ] Include MFC DLLs (mfc140u.dll, msvcp140.dll, vcruntime140.dll, etc.)
- [ ] Ensure the Visual C++ Redistributable is installed on target machines
- [ ] Ensure Microsoft Edge WebView2 Runtime is installed (included in Windows 11, download for Windows 10)
- [ ] Place the DLL in the same directory as your executable, or ensure it's in the PATH

## Troubleshooting

### "Cannot find MFCWebViewDLL.dll"
- Ensure the DLL is in the same directory as your executable
- Or add the DLL location to your system PATH
- Verify you're using the correct architecture (x86 vs x64)

### "Failed to create WebView2 environment"
- Ensure Microsoft Edge WebView2 Runtime is installed
- Download from: https://developer.microsoft.com/microsoft-edge/webview2/
- Windows 11 includes it by default

### Linker Error: "Cannot open file MFCWebViewDLL.lib"
- Check that the library directory is correctly added to Additional Library Directories
- Verify you're using the correct architecture (x86 vs x64)
- Ensure the DLL has been built successfully

### Runtime Error: "Entry point not found"
- Make sure you're using matching versions of the DLL and LIB files
- Rebuild the DLL if you've made changes

## WebView2 Runtime

This DLL uses **Microsoft Edge WebView2** for web browsing:

- **Windows 11**: WebView2 Runtime is included by default
- **Windows 10**: Download and install the WebView2 Runtime from Microsoft
- The DLL will display an error message if WebView2 Runtime is not found

## Support and Contribution

For issues, questions, or contributions, please refer to the project repository.

## License

Refer to the LICENSE file in the repository root.

---

**Last Updated:** 2025-10-18
**DLL Version:** 1.0.0
