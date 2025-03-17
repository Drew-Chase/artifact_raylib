#!/bin/bash
echo "=== Initializing artifact_raylib project ==="
echo

echo "Installing Conan dependencies..."
bash scripts/unix/conan-install.sh
if [ $? -ne 0 ]; then
    echo
    echo "=== Error initializing project! ==="
    exit $?
fi

echo "Building all configurations..."
bash scripts/unix/all.sh
if [ $? -ne 0 ]; then
    echo
    echo "=== Error initializing project! ==="
    exit $?
fi

echo
echo "=== Project initialized successfully! ==="