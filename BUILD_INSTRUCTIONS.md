# Build Instructions for MFC WebView DLL

This document provides detailed instructions for building and distributing the MFC WebView DLL.

## Prerequisites

### Required Software

1. **Visual Studio 2022** (or Visual Studio 2019/2017)
   - Install the "Desktop development with C++" workload
   - Ensure "MFC and ATL support" is selected in the installation

2. **Windows SDK**
   - Usually installed with Visual Studio
   - Windows 10 SDK (10.0.19041.0 or later recommended)

3. **Microsoft Edge WebView2 Runtime**
   - Included by default on Windows 11
   - Download for Windows 10 from: https://developer.microsoft.com/microsoft-edge/webview2/

4. **Platform Support**
   - The project is configured for both x86 (Win32) and x64 platforms

### Verify Installation

Open Visual Studio Developer Command Prompt and run:
```cmd
msbuild /version
```

## Building the DLL

### Method 1: Using Visual Studio IDE (Recommended)

1. **Open the Solution**
   ```
   Double-click: MFCWebViewDLL.sln
   ```

2. **Restore NuGet Packages**
   - Right-click on the solution in Solution Explorer
   - Select "Restore NuGet Packages"
   - Wait for the WebView2 SDK package to download

3. **Select Configuration**
   - Open the Configuration Manager (Build > Configuration Manager)
   - Select your desired configuration:
     - **Release|x64** (Recommended for production)
     - **Release|Win32** (For 32-bit support)
     - **Debug|x64** (For debugging)
     - **Debug|Win32** (For 32-bit debugging)

4. **Build the Project**
   - Menu: Build > Build Solution
   - Or press: `Ctrl+Shift+B`
   - Wait for the build to complete

5. **Verify Build Output**
   - Check the Output window for "Build succeeded"
   - Look for the generated files:
     - `x64\Release\MFCWebViewDLL.dll`
     - `x64\Release\MFCWebViewDLL.lib`
     - `Win32\Release\MFCWebViewDLL.dll`
     - `Win32\Release\MFCWebViewDLL.lib`

### Method 2: Using Command Line (MSBuild)

1. **Open Developer Command Prompt**
   - Search for "Developer Command Prompt for VS 2022"
   - Or use "Developer PowerShell for VS 2022"

2. **Navigate to Project Directory**
   ```cmd
   cd path\to\MFCWebViewDLL
   ```

3. **Build for x64 Release**
   ```cmd
   msbuild MFCWebViewDLL.sln /p:Configuration=Release /p:Platform=x64 /m
   ```

4. **Build for Win32 Release**
   ```cmd
   msbuild MFCWebViewDLL.sln /p:Configuration=Release /p:Platform=Win32 /m
   ```

5. **Build All Configurations**
   ```cmd
   msbuild MFCWebViewDLL.sln /p:Configuration=Release /p:Platform=x64 /m
   msbuild MFCWebViewDLL.sln /p:Configuration=Release /p:Platform=Win32 /m
   ```

### Build Output Location

After building, files will be in:
- **x64 builds:** `x64\[Configuration]\`
  - `MFCWebViewDLL.dll`
  - `MFCWebViewDLL.lib`
  - `MFCWebViewDLL.pdb` (debug symbols)

- **Win32 builds:** `Win32\[Configuration]\`
  - `MFCWebViewDLL.dll`
  - `MFCWebViewDLL.lib`
  - `MFCWebViewDLL.pdb` (debug symbols)

## Post-Build: Preparing Distribution

After building, you need to copy the files to the `Dist` folder for distribution.

### Using the Post-Build Script

1. **Run for x64 Release:**
   ```cmd
   PostBuild.bat x64 Release
   ```

2. **Run for Win32 Release:**
   ```cmd
   PostBuild.bat Win32 Release
   ```

This will automatically copy:
- DLL files to `Dist\dll\[platform]\`
- LIB files to `Dist\lib\[platform]\`
- PDB files to `Dist\dll\[platform]\` (if available)

### Manual Copy (Alternative)

If you prefer to copy manually:

**For x64:**
```cmd
copy x64\Release\MFCWebViewDLL.dll Dist\dll\x64\
copy x64\Release\MFCWebViewDLL.lib Dist\lib\x64\
```

**For Win32:**
```cmd
copy Win32\Release\MFCWebViewDLL.dll Dist\dll\x86\
copy Win32\Release\MFCWebViewDLL.lib Dist\lib\x86\
```

## Verifying the Build

### Check DLL Exports

Use `dumpbin` to verify the DLL exports:

```cmd
dumpbin /EXPORTS x64\Release\MFCWebViewDLL.dll
```

You should see:
- ShowWebViewDialog
- ShowWebViewDialogWithURL
- GetDLLVersion

### Check DLL Dependencies

```cmd
dumpbin /DEPENDENTS x64\Release\MFCWebViewDLL.dll
```

Expected dependencies:
- mfc140u.dll (or mfc140ud.dll for debug)
- KERNEL32.dll
- USER32.dll
- etc.

## Troubleshooting

### Build Error: "Cannot open include file: 'afxwin.h'"

**Solution:** Install MFC libraries
1. Open Visual Studio Installer
2. Modify your Visual Studio installation
3. Under "Desktop development with C++"
4. Check "C++ MFC for latest v143 build tools (x86 & x64)"
5. Click Modify and wait for installation

### Build Error: "LINK : fatal error LNK1104: cannot open file 'mfc140u.lib'"

**Solution:** Same as above - ensure MFC is installed

### Build Warning: "module machine type 'x64' conflicts with target machine type 'x86'"

**Solution:** Ensure you're building for the correct platform
- Clean the solution (Build > Clean Solution)
- Select the correct platform in Configuration Manager
- Rebuild

### Build Error: "error RC2104: undefined keyword or key name: IDD_WEBVIEW_DIALOG"

**Solution:** Ensure all resource files are present
- Verify `Resource.h` exists
- Verify `MFCWebViewDLL.rc` exists
- Clean and rebuild

### Runtime Error: "The application was unable to start correctly (0xc000007b)"

**Solution:** Platform mismatch
- Ensure you're using the correct DLL (x86 vs x64) for your application
- Rebuild both the DLL and your application for the same platform

## Clean Build

To ensure a fresh build:

1. **In Visual Studio:**
   - Build > Clean Solution
   - Build > Rebuild Solution

2. **Command Line:**
   ```cmd
   msbuild MFCWebViewDLL.sln /t:Clean /p:Configuration=Release /p:Platform=x64
   msbuild MFCWebViewDLL.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64
   ```

## Building for Distribution

To create a complete distribution package:

1. **Clean all previous builds**
   ```cmd
   msbuild MFCWebViewDLL.sln /t:Clean /p:Configuration=Release /p:Platform=x64
   msbuild MFCWebViewDLL.sln /t:Clean /p:Configuration=Release /p:Platform=Win32
   ```

2. **Build Release versions**
   ```cmd
   msbuild MFCWebViewDLL.sln /t:Build /p:Configuration=Release /p:Platform=x64 /m
   msbuild MFCWebViewDLL.sln /t:Build /p:Configuration=Release /p:Platform=Win32 /m
   ```

3. **Copy to Distribution**
   ```cmd
   PostBuild.bat x64 Release
   PostBuild.bat Win32 Release
   ```

4. **Verify Distribution Contents**
   - Check `Dist\include\` for headers
   - Check `Dist\dll\x86\` for Win32 DLL
   - Check `Dist\dll\x64\` for x64 DLL
   - Check `Dist\lib\x86\` for Win32 LIB
   - Check `Dist\lib\x64\` for x64 LIB
   - Check `Dist\README.md` for documentation

5. **Package for Distribution**
   - Zip the `Dist` folder
   - Name it: `MFCWebViewDLL-v1.0.0-dist.zip`

## Next Steps

After building:

1. **Test the DLL** - Create a test MFC application
2. **Review Documentation** - See `Dist\README.md`
3. **Deploy** - Share the `Dist` folder with other developers

## Additional Resources

- [MFC Desktop Applications](https://docs.microsoft.com/cpp/mfc/)
- [Creating a DLL](https://docs.microsoft.com/cpp/build/dlls-in-visual-cpp)
- [MSBuild Reference](https://docs.microsoft.com/visualstudio/msbuild/)

---

**Last Updated:** 2025-10-18
