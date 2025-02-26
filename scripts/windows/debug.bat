@echo off
echo Compiling debug
cd ..\..\

cmake.exe -DCMAKE_BUILD_TYPE=Debug -DPROFILE_NAME=debug -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake -G "MinGW Makefiles" -S %cd% -B %cd%\bin\obj\debug
cmake.exe --build bin\obj\debug --target clean -j 32
cmake.exe --build bin\obj\debug --target all -j 32
cd scripts\windows\