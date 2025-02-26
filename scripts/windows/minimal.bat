@echo off
echo Compiling minimal
cd ..\..\
cmake.exe -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=minimal -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake -G "MinGW Makefiles" -S %cd% -B %cd%\bin\obj\minimal
cmake.exe --build bin\obj\minimal --target clean -j 32
cmake.exe --build bin\obj\minimal --target all -j 32
cd scripts\windows\