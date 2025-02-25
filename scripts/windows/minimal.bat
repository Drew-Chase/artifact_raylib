@echo off
setlocal EnableDelayedExpansion

cd %~dp0\..\..

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
:: Create build directory
if not exist "bin\obj\shared" mkdir "bin\obj\shared"
cd "bin\obj\shared"

:: Configure and build
cmake -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DPROFILE_NAME=shared -DREMOVE_DEBUG_INFO=ON -DSTRIPPED_VERSION=ON -G "Ninja" ..\..\..
cmake --build . -j 32

cd ..\..\..