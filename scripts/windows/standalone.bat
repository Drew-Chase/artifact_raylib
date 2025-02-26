@echo off
echo Compiling standalone
cd ..\..\
cmake.exe --build bin\obj\standalone --target clean -j 32
cmake.exe --build bin\obj\standalone --target all -j 32