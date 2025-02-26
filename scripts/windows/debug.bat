@echo off
echo Compiling debug
cd ..\..\
cmake.exe --build bin\obj\debug --target clean -j 32
cmake.exe --build bin\obj\debug --target all -j 32
cd scripts\windows\