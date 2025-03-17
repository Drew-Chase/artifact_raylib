#!/bin/bash
echo "=== Building all configurations ==="
echo

echo "Building Debug configuration..."
bash scripts/unix/debug.sh
if [ $? -ne 0 ]; then
    echo
    echo "=== Error building configurations! ==="
    exit $?
fi

echo "Building Minimal configuration..."
bash scripts/unix/minimal.sh
if [ $? -ne 0 ]; then
    echo
    echo "=== Error building configurations! ==="
    exit $?
fi

echo "Building Standalone configuration..."
bash scripts/unix/standalone.sh
if [ $? -ne 0 ]; then
    echo
    echo "=== Error building configurations! ==="
    exit $?
fi

echo
echo "=== All configurations built successfully! ==="