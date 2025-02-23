#!/bin/bash

# Change to project root directory
cd "$(dirname "$0")/../.."

# Check if VCPKG_ROOT environment variable is set and valid
if [ -n "$VCPKG_ROOT" ] && [ -f "$VCPKG_ROOT/vcpkg" ]; then
    echo "Using VCPKG from environment: $VCPKG_ROOT"
else
    # Check if vcpkg is in PATH
    if command -v vcpkg &> /dev/null; then
        VCPKG_ROOT=$(dirname $(dirname $(which vcpkg)))
        echo "Using global VCPKG installation: $VCPKG_ROOT"
    # Check for local installation
    elif [ -d "vcpkg" ]; then
        VCPKG_ROOT="$PWD/vcpkg"
        echo "Using local VCPKG installation"
    else
        echo "VCPKG not found in environment, globally, or locally."
        read -p "Would you like to clone it? [y/N] " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            git clone https://github.com/Microsoft/vcpkg.git
            ./vcpkg/bootstrap-vcpkg.sh
            VCPKG_ROOT="$PWD/vcpkg"
        else
            echo "VCPKG installation skipped. Build may fail."
            exit 1
        fi
    fi
fi

# Create build directory
mkdir -p bin/obj/bundled
cd bin/obj/bundled

# Configure and build
cmake -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
      -DPROFILE_NAME=bundled \
      -DREMOVE_DEBUG_INFO=ON \
      -G "Ninja" ../../..
cmake --build . -j $(nproc)

cd ../../..