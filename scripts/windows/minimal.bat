@echo off
echo Compiling minimal
cd ..\..\
cmake.exe --build bin\obj\minimal --target clean -j 32
cmake.exe --build bin\obj\minimal --target all -j 32