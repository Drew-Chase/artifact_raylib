@echo off
echo Building All Configurations
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