# MFC WebView DLL - Integration Diagram

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                    CLIENT MFC APPLICATION                        │
│                                                                  │
│  ┌────────────────────────────────────────────────────────┐    │
│  │  #include "MFCWebViewDLL.h"                            │    │
│  │                                                         │    │
│  │  void CMyApp::OnShowWeb()                              │    │
│  │  {                                                      │    │
│  │      ShowWebViewDialog();  // ← Simple function call   │    │
│  │  }                                                      │    │
│  └────────────────────────────────────────────────────────┘    │
│                              │                                   │
│                              ▼                                   │
│         ┌────────────────────────────────────┐                 │
│         │  Links against MFCWebViewDLL.lib   │                 │
│         └────────────────────────────────────┘                 │
└─────────────────────────────┬───────────────────────────────────┘
                              │
                              │ Import Library
                              │ Resolves function addresses
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                     MFCWebViewDLL.dll                            │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │                  EXPORTED API                             │  │
│  │                                                           │  │
│  │  C Functions:                                            │  │
│  │  ┌─────────────────────────────────────────────────┐    │  │
│  │  │ ShowWebViewDialog()                             │    │  │
│  │  │ ShowWebViewDialogWithURL(LPCTSTR)               │    │  │
│  │  │ GetDLLVersion()                                 │    │  │
│  │  └─────────────────────────────────────────────────┘    │  │
│  │                                                           │  │
│  │  C++ Classes:                                            │  │
│  │  ┌─────────────────────────────────────────────────┐    │  │
│  │  │ class CMFCWebViewDLLApp : public CWinApp        │    │  │
│  │  │ class CWebViewDialog : public CDialogEx         │    │  │
│  │  └─────────────────────────────────────────────────┘    │  │
│  └──────────────────────────────────────────────────────────┘  │
│                              │                                   │
│                              ▼                                   │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │              INTERNAL IMPLEMENTATION                      │  │
│  │                                                           │  │
│  │  • CMFCWebViewDLLApp (DLL Application)                   │  │
│  │  • CWebViewDialog (Dialog Implementation)                │  │
│  │  • AFX_MANAGE_STATE (State Management)                   │  │
│  │  • Dialog Resources (IDD_WEBVIEW_DIALOG)                 │  │
│  │  • WebView Placeholder Control                           │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

## Data Flow

```
┌──────────────┐
│ Client App   │
│ Calls:       │
│              │
│ ShowWebView  │
│ Dialog()     │
└──────┬───────┘
       │
       │ 1. Function call via import library
       ▼
┌──────────────────────┐
│ MFCWebViewDLL.dll    │
│                      │
│ dllmain.cpp:        │
│ ShowWebViewDialog() │
└──────┬───────────────┘
       │
       │ 2. AFX_MANAGE_STATE (set DLL state)
       ▼
┌──────────────────────┐
│ Create CWebViewDialog│
│ instance             │
└──────┬───────────────┘
       │
       │ 3. Initialize dialog
       ▼
┌──────────────────────┐
│ Load dialog resource │
│ (IDD_WEBVIEW_DIALOG) │
└──────┬───────────────┘
       │
       │ 4. Show dialog modally
       ▼
┌──────────────────────┐
│ User interacts with  │
│ dialog (sees URL)    │
└──────┬───────────────┘
       │
       │ 5. User clicks OK/Cancel
       ▼
┌──────────────────────┐
│ Dialog closes,       │
│ returns to client    │
└──────────────────────┘
```

## File Dependencies

```
Client Application Files:
┌────────────────────────────────┐
│ MyApp.cpp                      │ → #include "MFCWebViewDLL.h"
│ MyApp.vcxproj                  │ → Links MFCWebViewDLL.lib
│ MyApp.exe (runtime)            │ → Loads MFCWebViewDLL.dll
└────────────────────────────────┘
                ↓ depends on
┌────────────────────────────────┐
│ Dist/include/MFCWebViewDLL.h   │ ← Header with API declarations
│ Dist/lib/x64/MFCWebViewDLL.lib │ ← Import library
│ Dist/dll/x64/MFCWebViewDLL.dll │ ← DLL with implementation
└────────────────────────────────┘
```

## Build and Distribution Flow

```
┌─────────────────────────────────────────────────────────┐
│ STEP 1: BUILD THE DLL                                   │
├─────────────────────────────────────────────────────────┤
│                                                          │
│ Visual Studio 2022                                       │
│   │                                                      │
│   ├─► Open MFCWebViewDLL.sln                           │
│   ├─► Build Solution (Release|x64)                      │
│   └─► Generates:                                        │
│         • x64\Release\MFCWebViewDLL.dll                 │
│         • x64\Release\MFCWebViewDLL.lib                 │
│                                                          │
└────────────────────────┬────────────────────────────────┘
                         │
                         ▼
┌─────────────────────────────────────────────────────────┐
│ STEP 2: COPY TO DISTRIBUTION                            │
├─────────────────────────────────────────────────────────┤
│                                                          │
│ Run: PostBuild.bat x64 Release                          │
│   │                                                      │
│   ├─► Copies DLL to Dist/dll/x64/                      │
│   └─► Copies LIB to Dist/lib/x64/                      │
│                                                          │
│ Headers already in Dist/include/                        │
│                                                          │
└────────────────────────┬────────────────────────────────┘
                         │
                         ▼
┌─────────────────────────────────────────────────────────┐
│ STEP 3: SHARE WITH OTHER DEVELOPERS                     │
├─────────────────────────────────────────────────────────┤
│                                                          │
│ Share the Dist/ folder containing:                      │
│   ├─ include/       (Headers)                           │
│   ├─ lib/x64/       (Import libraries)                  │
│   ├─ dll/x64/       (DLL files)                         │
│   └─ README.md      (Documentation)                     │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

## Runtime Dependencies

```
┌────────────────────────────────────────────────────────┐
│ Client Application (MyApp.exe)                         │
└────────────────────────┬───────────────────────────────┘
                         │
                         ├─► Requires: MFCWebViewDLL.dll
                         │
                         ├─► Requires: mfc140u.dll (MFC runtime)
                         │             or mfc140ud.dll (debug)
                         │
                         ├─► Requires: vcruntime140.dll
                         │
                         └─► Requires: msvcp140.dll
```

## Integration Steps Diagram

```
Developer wants to use MFC WebView DLL
                 │
                 ▼
     ┌───────────────────────┐
     │ 1. Get Dist folder    │
     └───────┬───────────────┘
             │
             ▼
     ┌───────────────────────┐
     │ 2. Add include dir    │
     │    to project         │
     └───────┬───────────────┘
             │
             ▼
     ┌───────────────────────┐
     │ 3. Add lib dir to     │
     │    project            │
     └───────┬───────────────┘
             │
             ▼
     ┌───────────────────────┐
     │ 4. Link against       │
     │    MFCWebViewDLL.lib  │
     └───────┬───────────────┘
             │
             ▼
     ┌───────────────────────┐
     │ 5. Include header in  │
     │    source code        │
     └───────┬───────────────┘
             │
             ▼
     ┌───────────────────────┐
     │ 6. Call exported      │
     │    functions          │
     └───────┬───────────────┘
             │
             ▼
     ┌───────────────────────┐
     │ 7. Copy DLL to exe    │
     │    directory          │
     └───────┬───────────────┘
             │
             ▼
        ✅ Done!
```

## API Usage Pattern

```cpp
// Pattern 1: Simple usage with default URL
void MyFunction1()
{
    ShowWebViewDialog();  
    // Shows google.com
}

// Pattern 2: Custom URL
void MyFunction2()
{
    ShowWebViewDialogWithURL(_T("https://www.microsoft.com"));
}

// Pattern 3: Advanced - using class directly
void MyFunction3()
{
    CWebViewDialog dlg;
    dlg.SetURL(_T("https://www.github.com"));
    if (dlg.DoModal() == IDOK)
    {
        // Handle OK
    }
}

// Pattern 4: Version check
void MyFunction4()
{
    LPCTSTR version = GetDLLVersion();
    // Returns "1.0.0"
}
```

## State Management Flow

```
┌────────────────────────────────────────────────────────────┐
│ Client App calls ShowWebViewDialog()                       │
└────────────────┬───────────────────────────────────────────┘
                 │
                 ▼
     ┌──────────────────────────┐
     │ AFX_MANAGE_STATE called  │
     │ Switches to DLL's module │
     │ state                    │
     └──────────┬───────────────┘
                │
                ▼
     ┌──────────────────────────┐
     │ Dialog resources loaded  │
     │ from DLL's resources     │
     └──────────┬───────────────┘
                │
                ▼
     ┌──────────────────────────┐
     │ Dialog shown to user     │
     └──────────┬───────────────┘
                │
                ▼
     ┌──────────────────────────┐
     │ On return, state         │
     │ automatically restored   │
     │ to client app            │
     └──────────────────────────┘
```

---

This diagram shows the complete architecture and integration flow of the MFC WebView DLL.
