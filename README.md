# MFC WebView DLL Project

This project provides a reusable MFC shared DLL that displays a WebView dialog. The DLL can be easily integrated into any MFC application to show web content.

## Quick Start

1. **Build the DLL:**
   - Open `MFCWebViewDLL.sln` in Visual Studio 2022
   - Select your configuration (Release|x64 recommended)
   - Build the solution

2. **Use the DLL:**
   - See `Dist/README.md` for detailed integration instructions
   - Copy the built DLL and LIB files to the Dist folder
   - Include the headers from `Dist/include` in your project

## Project Structure

```
MFCWebViewDLL/
├── MFCWebViewDLL.sln          # Visual Studio solution file
├── MFCWebViewDLL/             # DLL project folder
│   ├── *.cpp, *.h             # Source and header files
│   ├── *.rc                   # Resource files
│   ├── *.def                  # Module definition file
│   └── res/                   # Resource directory
└── Dist/                      # Distribution package
    ├── README.md              # API documentation
    ├── include/               # Header files for client apps
    ├── lib/                   # Import libraries (after build)
    └── dll/                   # DLL files (after build)
```

## Features

- ✅ MFC shared DLL project structure
- ✅ Exported dialog class with WebView placeholder
- ✅ C-style exported functions for easy integration
- ✅ Pre-configured resource files
- ✅ Distribution folder with headers
- ✅ Comprehensive API documentation
- ✅ Support for x86 and x64 platforms

## Requirements

- Visual Studio 2022 (or compatible version)
- Windows 10 SDK
- MFC libraries

## Build Instructions

### Using Visual Studio

1. Open `MFCWebViewDLL.sln`
2. Select configuration (Debug/Release, x86/x64)
3. Build Solution (Ctrl+Shift+B)
4. After build, manually copy:
   - `[Platform]\[Configuration]\MFCWebViewDLL.dll` → `Dist/dll/[platform]/`
   - `[Platform]\[Configuration]\MFCWebViewDLL.lib` → `Dist/lib/[platform]/`

### Using MSBuild (Command Line)

For Release x64:
```cmd
msbuild MFCWebViewDLL.sln /p:Configuration=Release /p:Platform=x64
```

For Release Win32:
```cmd
msbuild MFCWebViewDLL.sln /p:Configuration=Release /p:Platform=Win32
```

## Exported API

### C Functions
- `ShowWebViewDialog()` - Shows dialog with default URL
- `ShowWebViewDialogWithURL(LPCTSTR)` - Shows dialog with custom URL
- `GetDLLVersion()` - Returns DLL version string

### C++ Classes
- `CWebViewDialog` - Exported dialog class for advanced usage
- `CMFCWebViewDLLApp` - Main DLL application class

See `Dist/README.md` for detailed API documentation and usage examples.

## Usage Example

```cpp
#include "MFCWebViewDLL.h"

// Simple usage
void ShowMyWebView()
{
    ShowWebViewDialog();  // Shows google.com
}

// Custom URL
void ShowCustomWebView()
{
    ShowWebViewDialogWithURL(_T("https://www.microsoft.com"));
}
```

## Post-Build Steps

After building, organize the distribution:

1. Copy generated DLL files:
   ```
   Copy from: Win32\Release\MFCWebViewDLL.dll
          to: Dist\dll\x86\

   Copy from: x64\Release\MFCWebViewDLL.dll
          to: Dist\dll\x64\
   ```

2. Copy generated LIB files:
   ```
   Copy from: Win32\Release\MFCWebViewDLL.lib
          to: Dist\lib\x86\

   Copy from: x64\Release\MFCWebViewDLL.lib
          to: Dist\lib\x64\
   ```

3. The `Dist` folder is now ready to share with other applications!

## Testing

To verify the DLL:

1. Build the DLL in Release mode
2. Create a simple MFC test application
3. Link against the DLL
4. Call `ShowWebViewDialog()` from a button handler
5. Verify the dialog appears

## WebView Implementation Note

The current implementation uses a placeholder static control to simulate the WebView. For actual web browsing functionality, integrate Microsoft Edge WebView2:

1. Add WebView2 SDK via NuGet Package Manager
2. Replace the static placeholder with WebView2 control
3. Use WebView2 APIs to navigate and control the browser

## Known Limitations

- WebView placeholder is a static text control (not actual browser)
- For full web browsing, WebView2 integration is needed
- Requires MFC runtime DLLs on target machine

## License

See LICENSE file in the repository root.

## Contributing

Contributions are welcome! Please ensure code follows MFC best practices.
