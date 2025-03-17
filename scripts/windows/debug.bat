@echo off
echo === Building Debug configuration ===
echo.

REM Configure project with CMake
echo Configuring project...
cmake -B bin\obj\windows-x64\debug -G Ninja -DCMAKE_BUILD_TYPE=Debug ^
    -DPROFILE_NAME=debug -DSTRIPPED_VERSION=ON ^
    -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="%CD%\conan_provider.cmake"
if %errorlevel% neq 0 (
    echo.
    echo === Error configuring Debug configuration! ===
    exit /b %errorlevel%
)

REM Build project
echo Building project...
cmake --build bin\obj\windows-x64\debug -j %NUMBER_OF_PROCESSORS%
if %errorlevel% neq 0 (
    echo.
    echo === Error building Debug configuration! ===
    exit /b %errorlevel%
)

echo.
echo === Debug configuration built successfully! ===
echo Binary location: bin\artifact_raylib\debug\