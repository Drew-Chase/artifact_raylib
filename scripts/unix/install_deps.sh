#!/bin/bash
set -e

# Ensure the script is run as root.
if [ "$EUID" -ne 0 ]; then
    echo "Please run this script as root (e.g., using sudo)."
    exit 1
fi

# For apt-based systems (e.g., Debian, Ubuntu)
APT_DEPS="libxrandr-dev libxcursor-dev libxinerama-dev libxi-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev libopenal-dev cmake build-essential ninja-build git"

# For pacman-based systems (e.g., Arch Linux)
# Note: Arch package names can differ; often the Xorg libraries are included in the base system.
PACMAN_DEPS="xorg-server-devel libxrandr libxcursor libxinerama libxi glfw mesa glu openal cmake base-devel ninja-build git"

# For dnf-based systems (e.g., Fedora)
DNF_DEPS="libXrandr-devel libXcursor-devel libXinerama-devel libXi-devel glfw-devel mesa-libGL-devel mesa-libGLU-devel openal-soft-devel cmake gcc make ninja-build git"

echo "Detecting package manager..."

if command -v apt &> /dev/null; then
    echo "apt detected. Updating package lists and installing dependencies..."
    apt update
    apt install -y ${APT_DEPS}
elif command -v pacman &> /dev/null; then
    echo "pacman detected. Updating package lists and installing dependencies..."
    pacman -Syu --noconfirm
    pacman -S --noconfirm ${PACMAN_DEPS}
elif command -v dnf &> /dev/null; then
    echo "dnf detected. Installing dependencies..."
    dnf install -y ${DNF_DEPS}
else
    echo "No supported package manager found (apt, pacman, or dnf)."
    exit 1
fi

echo "All dependencies have been installed successfully."
