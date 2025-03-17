@echo off
echo === Building Standalone configuration ===
echo.

REM Configure project with CMake
echo Configuring project...
cmake -B bin/obj/winx64/standalone -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=standalone -DREMOVE_DEBUG_INFO=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"
if %errorlevel% neq 0 goto error

REM Build project
echo Building project...
cmake --build bin/obj/winx64/standalone -j 32
if %errorlevel% neq 0 goto error

echo.
echo === Standalone configuration built successfully! ===
echo Binary location: bin/artifact_raylib/standalone/
goto end

:error
echo.
echo === Error building Standalone configuration! ===
exit /b %errorlevel%

:end