#!/bin/bash
echo "=== Installing Conan dependencies ==="
echo

# Check for Conan installation
if ! command -v conan &> /dev/null; then
    echo "Error: Conan is not installed or not in PATH"
    echo "Please install Conan with: pip install conan"
    exit 1
fi

# Create conan_provider.cmake for CMake integration
echo "Generating conan_provider.cmake..."
conan install . --output-folder=bin/obj/conan -s build_type=Debug --build=missing
if [ $? -ne 0 ]; then
    echo "Error: Failed to install Conan dependencies"
    exit $?
fi

echo
echo "=== Conan dependencies installed successfully ==="