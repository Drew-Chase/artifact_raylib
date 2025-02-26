@echo off
echo Compiling standalone
cd ..\..\
cmake.exe -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=standalone -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake -G "MinGW Makefiles" -S %cd% -B %cd%\bin\obj\standalone
cmake.exe --build bin\obj\standalone --target clean -j 32
cmake.exe --build bin\obj\standalone --target all -j 32
cd scripts\windows\