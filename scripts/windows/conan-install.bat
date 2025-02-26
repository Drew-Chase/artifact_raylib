@echo off
echo Installing Conan Packages...
conan profile detect --force
conan install . --build=missing