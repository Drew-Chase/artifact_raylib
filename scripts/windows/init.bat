@echo off
echo Initializing artifact raylib project
mkdir ..\..\bin\obj\debug
mkdir ..\..\bin\obj\minimal
mkdir ..\..\bin\obj\standalone
call conan-install.bat
call all.bat