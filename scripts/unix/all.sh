#!/bin/bash
echo "Building All Configurations"

# Build Debug configuration
echo "Building Debug configuration..."
bash scripts/windows/debug.bat
if [ $? -ne 0 ]; then
  echo "Build failed!"
  exit 1
fi

# Build Shared configuration
echo "Building Shared configuration..."
bash scripts/windows/minimal.bat
if [ $? -ne 0 ]; then
  echo "Build failed!"
  exit 1
fi

# Build Bundled configuration
echo "Building Bundled configuration..."
bash scripts/windows/standalone.bat
if [ $? -ne 0 ]; then
  echo "Build failed!"
  exit 1
fi

echo "All configurations built successfully!"