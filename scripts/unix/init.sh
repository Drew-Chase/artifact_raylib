#!/bin/bash
set -e

echo "=== Initializing artifact_raylib project ==="
echo

echo "Installing Conan dependencies..."
./scripts/unix/conan-install.sh

echo "Building all configurations..."
./scripts/unix/all.sh

echo
echo "=== Project initialized successfully! ==="