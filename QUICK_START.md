# Quick Start Guide - MFC WebView DLL

This guide will help you quickly get started with building and using the MFC WebView DLL.

## For the DLL Developer (You)

### Step 1: Build the DLL

1. **Open the solution:**
   ```
   Open MFCWebViewDLL.sln in Visual Studio 2022
   ```

2. **Restore NuGet packages:**
   - Right-click on the solution > Restore NuGet Packages

3. **Select configuration:**
   - Configuration: Release
   - Platform: x64 (or Win32 for 32-bit)

4. **Build:**
   - Press `Ctrl+Shift+B` or select Build > Build Solution

5. **Copy to distribution:**
   ```cmd
   PostBuild.bat x64 Release
   ```

That's it! The DLL is now ready in the `Dist` folder.

### Step 2: Share with Other Developers

Share the entire `Dist` folder which contains:
- Header files in `include/`
- Import libraries in `lib/x86/` and `lib/x64/`
- DLL files in `dll/x86/` and `dll/x64/`
- API documentation in `README.md`

## For Application Developers Using the DLL

### Step 1: Add to Your Project

1. **Copy the Dist folder** to your project directory

2. **Ensure WebView2 Runtime is installed:**
   - Included by default on Windows 11
   - Download for Windows 10: https://developer.microsoft.com/microsoft-edge/webview2/

3. **Configure includes:**
   - Project Properties > C/C++ > General > Additional Include Directories
   - Add: `$(ProjectDir)Dist\include`

4. **Configure linker:**
   - Project Properties > Linker > General > Additional Library Directories
   - Add: `$(ProjectDir)Dist\lib\x64` (or x86)
   
   - Project Properties > Linker > Input > Additional Dependencies
   - Add: `MFCWebViewDLL.lib`

5. **Copy DLL to output:**
   - Copy `Dist\dll\x64\MFCWebViewDLL.dll` to your exe directory

### Step 2: Use in Your Code

```cpp
#include "MFCWebViewDLL.h"

void CMyApp::OnShowWeb()
{
    // That's it - one line!
    ShowWebViewDialog();
}

void CMyApp::OnShowCustomURL()
{
    ShowWebViewDialogWithURL(_T("https://www.microsoft.com"));
}
```

## Troubleshooting

**Q: Build fails with "cannot open include file: 'afxwin.h'"**

A: Install MFC support in Visual Studio:
- Open Visual Studio Installer
- Modify installation
- Check "C++ MFC for latest build tools"

**Q: "Cannot find MFCWebViewDLL.dll" at runtime**

A: Copy the DLL to your application's directory

**Q: "Failed to create WebView2 environment"**

A: Install Microsoft Edge WebView2 Runtime from https://developer.microsoft.com/microsoft-edge/webview2/

**Q: Linker error LNK2019**

A: Ensure MFCWebViewDLL.lib is in Additional Dependencies

## Documentation

- **README.md** - Project overview
- **BUILD_INSTRUCTIONS.md** - Detailed build guide
- **USAGE_EXAMPLE.md** - Complete code examples
- **Dist/README.md** - API reference

## What's Next?

1. Build the DLL (see above)
2. Create a test MFC application
3. Integrate the DLL using the steps above
4. Test by calling `ShowWebViewDialog()` - it will display actual web content!

## WebView2 Runtime

This DLL uses Microsoft Edge WebView2 for actual web browsing:
- **Windows 11**: Already included
- **Windows 10**: Download from Microsoft's website

---

Need help? See the full documentation files!
