@echo off
echo Installing Conan Packages...
cd ..\..\
conan profile detect --force
conan install . --build=missing
cd scripts\windows\