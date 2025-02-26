@echo off
echo Building All Configurations
:: Build Debug configuration
echo Building Debug configuration...
call debug.bat
if %ERRORLEVEL% neq 0 goto :error

:: Build Shared configuration
echo Building Shared configuration...
call minimal.bat
if %ERRORLEVEL% neq 0 goto :error

:: Build Bundled configuration
echo Building Bundled configuration...
call standalone.bat
if %ERRORLEVEL% neq 0 goto :error

echo All configurations built successfully!
goto :end

:error
echo Build failed!
exit /b 1

:end