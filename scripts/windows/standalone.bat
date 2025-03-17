@echo off
echo === Building Standalone configuration ===
echo.

REM Configure project with CMake
echo Configuring project...
cmake -B bin\obj\windows-x64\standalone -G Ninja -DCMAKE_BUILD_TYPE=Release ^
    -DPROFILE_NAME=standalone -DREMOVE_DEBUG_INFO=ON ^
    -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="%CD%\conan_provider.cmake"
if %errorlevel% neq 0 (
    echo.
    echo === Error configuring Standalone configuration! ===
    exit /b %errorlevel%
)

REM Build project
echo Building project...
cmake --build bin\obj\windows-x64\standalone -j %NUMBER_OF_PROCESSORS%
if %errorlevel% neq 0 (
    echo.
    echo === Error building Standalone configuration! ===
    exit /b %errorlevel%
)

echo.
echo === Standalone configuration built successfully! ===
echo Binary location: bin\artifact_raylib\standalone\