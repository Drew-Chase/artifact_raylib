# Build Documentation

[![Build and Test](https://github.com/Drew-Chase/artifact_raylib/actions/workflows/build.yml/badge.svg)](https://github.com/Drew-Chase/artifact_raylib/actions/workflows/build.yml)

## Table of Contents

- [Prerequisites](#prerequisites)
- [Dependencies](#dependencies)
- [Building the Project](#building-the-project)
    - [Windows](#windows)
    - [Linux/macOS](#linuxmacos)
- [Build Configurations](#build-configurations)
- [Build Scripts](#build-scripts)
- [Troubleshooting](#troubleshooting)

## Prerequisites

Before building the project, ensure you have the following tools installed:

- **CMake** (version 3.30 or higher)
- **Git** (for source code management)
- **C++ Compiler** with C++20 support:
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

```shell script
sudo apt update
sudo apt install build-essential cmake ninja-build git python3-pip
pip3 install conan
```

For macOS:

```shell script
# Install Homebrew if not installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required tools
brew install cmake ninja git python
pip3 install conan
```

2. **Clone the Repository**

```shell script
git clone https://github.com/Drew-Chase/artifact_raylib.git
cd artifact_raylib
```

3. **Build the Project**

```shell script
# Make scripts executable
chmod +x scripts/unix/*.sh

# Initialize project and build all configurations
./scripts/unix/init.sh

# Or build specific configurations:
./scripts/unix/debug.sh       # Debug configuration
./scripts/unix/minimal.sh     # Minimal configuration
./scripts/unix/standalone.sh  # Standalone configuration
```

## Build Configurations

The project supports three build configurations:

1. **Debug**
    - Includes debug symbols
    - No optimization
    - Suitable for development and debugging

2. **Minimal**
    - Release build with optimizations
    - Debug symbols removed
    - Dynamic linking where possible
    - Suitable for development testing

3. **Standalone**
    - Release build with optimizations
    - Debug symbols removed
    - Static linking where possible
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

### Unix Scripts (Linux/macOS)

- `init.sh` - Initializes the project by installing dependencies and building all configurations
- `conan-install.sh` - Installs Conan dependencies
- `debug.sh` - Builds debug configuration
- `minimal.sh` - Builds minimal configuration
- `standalone.sh` - Builds standalone configuration

## Build Output

Built binaries are placed in the `bin/obj/` directory under their respective configuration folders.

The main changes made to the README include:

1. Replaced vcpkg with Conan as the package manager
2. Updated prerequisites to include Conan and removed vcpkg
3. Added information about the new script structure, including `init.bat` and `conan-install.bat`
4. Updated the build configurations to reflect the actual configurations (debug, minimal, standalone)
5. Modified the build instructions to use the new initialization process
6. Updated the script descriptions to match the current script set