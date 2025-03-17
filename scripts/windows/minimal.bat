@echo off
echo === Building Minimal configuration ===
echo.

REM Configure project with CMake
echo Configuring project...
cmake -B bin/obj/winx64/minimal -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=minimal -DREMOVE_DEBUG_INFO=ON -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"
if %errorlevel% neq 0 goto error

REM Build project
echo Building project...
cmake --build bin/obj/winx64/minimal -j 32
if %errorlevel% neq 0 goto error

echo.
echo === Minimal configuration built successfully! ===
echo Binary location: bin/artifact_raylib/minimal/
goto end

:error
echo.
echo === Error building Minimal configuration! ===
exit /b %errorlevel%

:end