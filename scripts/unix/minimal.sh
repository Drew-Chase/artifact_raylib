#!/bin/bash
set -e

echo "=== Building Minimal configuration ==="
echo

# Detect OS for proper output path
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS_ARCH="macos-$(uname -m)"
else
    OS_ARCH="linux-$(uname -m)"
fi

# Configure project with CMake
echo "Configuring project..."
cmake -B bin/obj/$OS_ARCH/minimal -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=minimal -DREMOVE_DEBUG_INFO=ON -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"

# Build project
echo "Building project..."
cmake --build bin/obj/$OS_ARCH/minimal -j $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo
echo "=== Minimal configuration built successfully! ==="
echo "Binary location: bin/artifact_raylib/minimal/"