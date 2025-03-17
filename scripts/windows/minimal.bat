@echo off
echo === Building Minimal configuration ===
echo.

REM Configure project with CMake
echo Configuring project...
cmake -B bin\obj\windows-x64\minimal -G Ninja -DCMAKE_BUILD_TYPE=Release ^
    -DPROFILE_NAME=minimal -DREMOVE_DEBUG_INFO=ON -DSTRIPPED_VERSION=ON ^
    -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="%CD%\conan_provider.cmake"
if %errorlevel% neq 0 (
    echo.
    echo === Error configuring Minimal configuration! ===
    exit /b %errorlevel%
)

REM Build project
echo Building project...
cmake --build bin\obj\windows-x64\minimal -j %NUMBER_OF_PROCESSORS%
if %errorlevel% neq 0 (
    echo.
    echo === Error building Minimal configuration! ===
    exit /b %errorlevel%
)

echo.
echo === Minimal configuration built successfully! ===
echo Binary location: bin\artifact_raylib\minimal\