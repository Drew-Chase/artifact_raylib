@echo off
echo === Initializing artifact_raylib project ===
echo.

echo Installing Conan dependencies...
call scripts\windows\conan-install.bat
if %errorlevel% neq 0 (
    echo.
    echo === Error initializing project! ===
    exit /b %errorlevel%
)

echo Building all configurations...
call scripts\windows\all.bat
if %errorlevel% neq 0 (
    echo.
    echo === Error initializing project! ===
    exit /b %errorlevel%
)

echo.
echo === Project initialized successfully! ===