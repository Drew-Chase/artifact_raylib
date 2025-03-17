#!/bin/bash
echo "=== Building Standalone configuration ==="
echo

# Detect OS for proper output path
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS_ARCH="macos-$(uname -m)"
else
    OS_ARCH="linux-$(uname -m)"
fi

# Configure project with CMake
echo "Configuring project..."
cmake -B bin/obj/$OS_ARCH/standalone -G Ninja -DCMAKE_BUILD_TYPE=Release \
    -DPROFILE_NAME=standalone -DREMOVE_DEBUG_INFO=ON \
    -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="$(pwd)/conan_provider.cmake"
if [ $? -ne 0 ]; then
    echo
    echo "=== Error configuring Standalone configuration! ==="
    exit $?
fi

# Build project
echo "Building project..."
PROCS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
cmake --build bin/obj/$OS_ARCH/standalone -j $PROCS
if [ $? -ne 0 ]; then
    echo
    echo "=== Error building Standalone configuration! ==="
    exit $?
fi

echo
echo "=== Standalone configuration built successfully! ==="
echo "Binary location: bin/artifact_raylib/standalone/"