@echo off
echo === Building all configurations ===
echo.

echo Building Debug configuration...
call scripts\windows\debug.bat
if %errorlevel% neq 0 goto error

echo Building Minimal configuration...
call scripts\windows\minimal.bat
if %errorlevel% neq 0 goto error

echo Building Standalone configuration...
call scripts\windows\standalone.bat
if %errorlevel% neq 0 goto error

echo.
echo === All configurations built successfully! ===
goto end

:error
echo.
echo === Error building configurations! ===
exit /b %errorlevel%

:end