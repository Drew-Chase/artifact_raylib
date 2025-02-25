@echo off
setlocal EnableDelayedExpansion

cd %~dp0\..\..
echo Building All Configurations

:: Check if VCPKG_ROOT environment variable is set
if defined VCPKG_ROOT (
    if exist "!VCPKG_ROOT!\vcpkg.exe" (
        echo Using VCPKG from environment: !VCPKG_ROOT!
        goto :found_vcpkg
    )
)

:: Check if VCPKG exists globally
where vcpkg.exe >nul 2>nul
if %ERRORLEVEL% equ 0 (
    for /f "tokens=*" %%i in ('where vcpkg.exe') do (
        set "VCPKG_ROOT=%%~dpi.."
        echo Using global VCPKG installation: !VCPKG_ROOT!
        goto :found_vcpkg
    )
)

:: Check for local installation
if exist "vcpkg" (
    set "VCPKG_ROOT=%CD%\vcpkg"
    echo Using local VCPKG installation
    goto :found_vcpkg
)

:: No VCPKG found, ask to install
echo VCPKG not found in environment, globally, or locally.
echo Would you like to clone it? [Y/N]
set /p INSTALL=
if /i "!INSTALL!"=="Y" (
    git clone https://github.com/Microsoft/vcpkg.git
    call .\vcpkg\bootstrap-vcpkg.bat
    set "VCPKG_ROOT=%CD%\vcpkg"
) else (
    echo VCPKG installation skipped. Build may fail.
    exit /b 1
)

:found_vcpkg
:: Build Debug configuration
echo Building Debug configuration...
call scripts\windows\debug.bat
if %ERRORLEVEL% neq 0 goto :error

:: Build Shared configuration
echo Building Shared configuration...
call scripts\windows\minimal.bat
if %ERRORLEVEL% neq 0 goto :error

:: Build Bundled configuration
echo Building Bundled configuration...
call scripts\windows\standalone.bat
if %ERRORLEVEL% neq 0 goto :error

echo All configurations built successfully!
goto :end

:error
echo Build failed!
exit /b 1

:end