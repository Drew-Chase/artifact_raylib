#!/bin/bash

# Change to project root directory
cd "$(dirname "$0")/../.."

echo "Building All Configurations"

# Determine OS type for proper messaging
OS_TYPE=$(uname -s)
if [ "$OS_TYPE" = "Darwin" ]; then
    OS_NAME="macOS"
else
    OS_NAME="Linux"
fi

echo "Building on $OS_NAME"

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

# Build Debug configuration
echo "Building Debug configuration..."
if ! scripts/unix/debug.sh; then
    echo "Build failed!"
    exit 1
fi

# Build Shared configuration
echo "Building Shared configuration..."
if ! scripts/unix/shared.sh; then
    echo "Build failed!"
    exit 1
fi

# Build Bundled configuration
echo "Building Bundled configuration..."
if ! scripts/unix/bundled.sh; then
    echo "Build failed!"
    exit 1
fi

echo "All configurations built successfully!"