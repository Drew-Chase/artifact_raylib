# Build Documentation

[![Build and Test](https://github.com/Drew-Chase/artifact_raylib/actions/workflows/build.yml/badge.svg)](https://github.com/Drew-Chase/artifact_raylib/actions/workflows/build.yml)

## Table of Contents

- [Prerequisites](#prerequisites)
- [Dependencies](#dependencies)
- [Building the Project](#building-the-project)
    - [Windows](#windows)
    - [Linux/macOS](#linuxmacos)
- [Manual Build with CMake and Conan](#manual-build-with-cmake-and-conan)
- [Build Configurations](#build-configurations)
- [Build Scripts](#build-scripts)
- [Troubleshooting](#troubleshooting)

## Prerequisites

Before building the project, ensure you have the following tools installed:

- **CMake** (version 3.22 or higher)
- **Git** (for source code management)
- **C++ Compiler** with C++23 support:
    - Windows: Visual Studio 2019 or newer with C++ workload
    - Linux: GCC 10+ or Clang 12+
    - macOS: Xcode Command Line Tools or AppleClang 12+
- **Ninja** build system
- **Conan** package manager (version 2.0 or higher)

## Dependencies

The project uses the following dependencies managed through Conan:

- raylib (version 5.5 or higher)

Dependencies are automatically handled by Conan through the project's `conandata.yml`.

## Building the Project

### Windows

1. **Install Prerequisites**

```powershell
# Install Chocolatey (if not installed)
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# Install required tools
choco install cmake ninja git visualstudio2022-workload-vctools python
pip install conan
```

2. **Clone the Repository**

```batch
git clone https://github.com/Drew-Chase/artifact_raylib.git
cd artifact_raylib
```

3. **Build the Project**

```batch
# Initialize the project (installs dependencies and builds all configurations)
scripts\windows\init.bat

# Or build specific configurations:
scripts\windows\debug.bat     # Debug configuration
scripts\windows\minimal.bat   # Minimal configuration
scripts\windows\standalone.bat # Standalone configuration
```

### Linux/macOS

1. **Install Prerequisites**

For Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake ninja-build git python3-pip
pip3 install conan
```
For macOS:
```bash
# Install Homebrew if not installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required tools
brew install cmake ninja git python
pip3 install conan
```
2. **Clone the Repository**
```bash
git clone https://github.com/Drew-Chase/artifact_raylib.git
cd artifact_raylib
```
3. **Build the Project**
```bash
# Make scripts executable
chmod +x scripts/unix/*.sh

# Initialize project and build all configurations
./scripts/unix/init.sh

# Or build specific configurations:
./scripts/unix/debug.sh       # Debug configuration
./scripts/unix/minimal.sh     # Minimal configuration
./scripts/unix/standalone.sh  # Standalone configuration
```
## Manual Build with CMake and Conan

If you prefer to build manually without using the provided scripts, follow these steps:

1. **Setup Conan Provider**

First, create a `conan_provider.cmake` file in the project root to let CMake find the Conan dependencies:
```bash
# Generate the conan provider file
conan install . --output-folder=. -s build_type=Debug
```
2. **Configure CMake Project**

For Debug configuration:
```bash
# Windows
cmake -B bin/obj/winx64/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DPROFILE_NAME=debug -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"

# Linux/macOS
cmake -B bin/obj/linux-amd64/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DPROFILE_NAME=debug -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"
```
For Minimal configuration:
```bash
# Windows
cmake -B bin/obj/winx64/minimal -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=minimal -DREMOVE_DEBUG_INFO=ON -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"

# Linux/macOS
cmake -B bin/obj/linux-amd64/minimal -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=minimal -DREMOVE_DEBUG_INFO=ON -DSTRIPPED_VERSION=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"
```
For Standalone configuration:
```bash
# Windows
cmake -B bin/obj/winx64/standalone -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=standalone -DREMOVE_DEBUG_INFO=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"

# Linux/macOS
cmake -B bin/obj/linux-amd64/standalone -G Ninja -DCMAKE_BUILD_TYPE=Release -DPROFILE_NAME=standalone -DREMOVE_DEBUG_INFO=ON -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="conan_provider.cmake"
```
3. **Build the Project**
```bash
# Build using the desired configuration
cmake --build bin/obj/winx64/debug -j 32     # For Windows Debug
cmake --build bin/obj/linux-amd64/debug -j 32 # For Linux/macOS Debug

# Similar commands for minimal and standalone configurations
cmake --build bin/obj/winx64/minimal -j 32
cmake --build bin/obj/winx64/standalone -j 32
```
## Build Configurations

The project supports three build configurations:

1. **Debug**
    - Includes debug symbols
    - Development build with debugging information
    - Stripped version with certain flags removed
    - Suitable for development and debugging

2. **Minimal**
    - Release build with optimizations
    - Debug symbols removed
    - Stripped version with certain flags removed
    - Suitable for development testing

3. **Standalone**
    - Release build with optimizations
    - Debug symbols removed
    - No stripping of flags
    - Suitable for distribution

## Build Scripts

The project includes platform-specific build scripts located in:

- `scripts/windows/` - Windows batch scripts
- `scripts/unix/` - Linux and macOS shell scripts

### Windows Scripts

- `init.bat` - Initializes the project by installing dependencies and building all configurations
- `conan-install.bat` - Installs Conan dependencies
- `debug.bat` - Builds debug configuration
- `minimal.bat` - Builds minimal configuration
- `standalone.bat` - Builds standalone configuration

### Unix Scripts

- `init.sh` - Initializes the project by installing dependencies and building all configurations
- `conan-install.sh` - Installs Conan dependencies
- `debug.sh` - Builds debug configuration
- `minimal.sh` - Builds minimal configuration
- `standalone.sh` - Builds standalone configuration

## Troubleshooting

If you encounter build issues, try the following:

1. Ensure all prerequisites are correctly installed and their versions meet the requirements
2. Clear the build directory and rebuild
3. Update Conan dependencies with `conan install . --update`
4. Check compiler compatibility with C++23