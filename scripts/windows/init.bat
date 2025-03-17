@echo off
echo === Initializing artifact_raylib project ===
echo.

echo Installing Conan dependencies...
call scripts\windows\conan-install.bat
if %errorlevel% neq 0 goto error

echo Building all configurations...
call scripts\windows\all.bat
if %errorlevel% neq 0 goto error

echo.
echo === Project initialized successfully! ===
goto end

:error
echo.
echo === Error initializing project! ===
exit /b %errorlevel%

:end