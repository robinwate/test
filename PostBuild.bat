@echo off
REM Post-Build Script to Copy DLL and LIB files to Distribution Folder
REM Usage: PostBuild.bat [Platform] [Configuration]
REM Example: PostBuild.bat x64 Release

setlocal

set PLATFORM=%1
set CONFIG=%2

if "%PLATFORM%"=="" (
    echo Error: Platform not specified
    echo Usage: PostBuild.bat [Platform] [Configuration]
    echo Example: PostBuild.bat x64 Release
    exit /b 1
)

if "%CONFIG%"=="" (
    echo Error: Configuration not specified
    echo Usage: PostBuild.bat [Platform] [Configuration]
    echo Example: PostBuild.bat x64 Release
    exit /b 1
)

REM Determine target directory based on platform
if /i "%PLATFORM%"=="Win32" (
    set DISTPLATFORM=x86
) else if /i "%PLATFORM%"=="x64" (
    set DISTPLATFORM=x64
) else (
    echo Error: Unknown platform "%PLATFORM%"
    exit /b 1
)

REM Set source and destination paths
set SRCDIR=%PLATFORM%\%CONFIG%
set DSTDLL=Dist\dll\%DISTPLATFORM%
set DSTLIB=Dist\lib\%DISTPLATFORM%

echo ====================================
echo MFC WebView DLL Post-Build Copy
echo ====================================
echo Platform: %PLATFORM% (Dist: %DISTPLATFORM%)
echo Configuration: %CONFIG%
echo Source: %SRCDIR%
echo ====================================

REM Create destination directories if they don't exist
if not exist "%DSTDLL%" mkdir "%DSTDLL%"
if not exist "%DSTLIB%" mkdir "%DSTLIB%"

REM Copy DLL file
if exist "%SRCDIR%\MFCWebViewDLL.dll" (
    echo Copying DLL to %DSTDLL%...
    copy /Y "%SRCDIR%\MFCWebViewDLL.dll" "%DSTDLL%\"
    if %ERRORLEVEL% EQU 0 (
        echo   [OK] DLL copied successfully
    ) else (
        echo   [ERROR] Failed to copy DLL
        exit /b 1
    )
) else (
    echo   [WARNING] DLL not found: %SRCDIR%\MFCWebViewDLL.dll
)

REM Copy LIB file
if exist "%SRCDIR%\MFCWebViewDLL.lib" (
    echo Copying LIB to %DSTLIB%...
    copy /Y "%SRCDIR%\MFCWebViewDLL.lib" "%DSTLIB%\"
    if %ERRORLEVEL% EQU 0 (
        echo   [OK] LIB copied successfully
    ) else (
        echo   [ERROR] Failed to copy LIB
        exit /b 1
    )
) else (
    echo   [WARNING] LIB not found: %SRCDIR%\MFCWebViewDLL.lib
)

REM Copy PDB file if available (for debugging)
if exist "%SRCDIR%\MFCWebViewDLL.pdb" (
    echo Copying PDB to %DSTDLL%...
    copy /Y "%SRCDIR%\MFCWebViewDLL.pdb" "%DSTDLL%\"
    if %ERRORLEVEL% EQU 0 (
        echo   [OK] PDB copied successfully
    ) else (
        echo   [WARNING] Failed to copy PDB
    )
)

echo ====================================
echo Post-build copy completed!
echo ====================================

endlocal
exit /b 0
