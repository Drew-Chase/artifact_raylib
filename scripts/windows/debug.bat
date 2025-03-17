@echo off
echo === Building Debug configuration ===
echo.

REM Configure project with CMake
echo Configuring project...
cmake -B bin/obj/winx64/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DPROFILE_NAME=debug -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"
if %errorlevel% neq 0 goto error

REM Build project
echo Building project...
cmake --build bin/obj/winx64/debug -j 32
if %errorlevel% neq 0 goto error

echo.
echo === Debug configuration built successfully! ===
echo Binary location: bin/artifact_raylib/debug/
goto end

:error
echo.
echo === Error building Debug configuration! ===
exit /b %errorlevel%

:end