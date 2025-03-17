#!/bin/bash
set -e

echo "=== Building all configurations ==="
echo

echo "Building Debug configuration..."
./scripts/unix/debug.sh

echo "Building Minimal configuration..."
./scripts/unix/minimal.sh

echo "Building Standalone configuration..."
./scripts/unix/standalone.sh

echo
echo "=== All configurations built successfully! ==="