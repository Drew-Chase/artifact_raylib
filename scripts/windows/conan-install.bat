@echo off
echo === Installing Conan dependencies ===
echo.

REM Check for Conan installation
where conan >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: Conan is not installed or not in PATH
    echo Please install Conan with: pip install conan
    exit /b 1
)

REM Create conan_provider.cmake for CMake integration
echo Generating conan_provider.cmake...
conan install . --output-folder=. -s build_type=Debug
if %errorlevel% neq 0 (
    echo Error: Failed to install Conan dependencies
    exit /b %errorlevel%
)

echo.
echo === Conan dependencies installed successfully ===