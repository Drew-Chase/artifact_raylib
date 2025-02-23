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
- **Git** (for vcpkg and source code management)
- **C++ Compiler** with C++20 support:
    - Windows: Visual Studio 2019 or newer with C++ workload
    - Linux: GCC 10+ or Clang 12+
    - macOS: Xcode Command Line Tools or AppleClang 12+
- **Ninja** build system
- **vcpkg** (will be installed automatically by build scripts if not present)

## Dependencies

The project uses the following dependencies managed through vcpkg:
- raylib (version 5.5 or higher)

Dependencies are automatically handled by vcpkg through the `vcpkg.json` manifest file.

## Building the Project

### Windows

1. **Install Prerequisites**
```powershell
# Install Chocolatey (if not installed)
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# Install required tools
choco install cmake ninja git visualstudio2022-workload-vctools
```

2. **Clone the Repository**
```batch
git clone https://github.com/Drew-Chase/artifact_raylib.git
   cd artifact_raylib
```

3. **Build the Project**
```batch
# Build debug configuration
   scripts\windows\debug.bat

   # Build release configuration
   scripts\windows\shared.bat

   # Build all configurations
   scripts\windows\all.bat
```

### Linux/macOS

1. **Install Prerequisites**

   For Ubuntu/Debian:
```shell script
sudo apt update
   sudo apt install build-essential cmake ninja-build git
```

For macOS:
```shell script
# Install Homebrew if not installed
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

   # Install required tools
   brew install cmake ninja git
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

   # Build debug configuration
   ./scripts/unix/debug.sh

   # Build release configuration
   ./scripts/unix/shared.sh

   # Build all configurations
   ./scripts/unix/all.sh
```

## Build Configurations

The project supports three build configurations:

1. **Debug** (`debug`)
    - Includes debug symbols
    - No optimization
    - Suitable for development and debugging

2. **Shared** (`shared`)
    - Release build with optimizations
    - Debug symbols removed
    - Dynamic linking where possible
    - Suitable for distribution with shared libraries

3. **Bundled** (`bundled`)
    - Release build with optimizations
    - Debug symbols removed
    - Static linking where possible
    - Suitable for standalone distribution

## Build Scripts

The project includes platform-specific build scripts located in:
- `scripts/windows/` - Windows batch scripts
- `scripts/unix/` - Linux and macOS shell scripts

### Windows Scripts
- `debug.bat` - Builds debug configuration
- `shared.bat` - Builds shared configuration
- `bundled.bat` - Builds bundled configuration
- `all.bat` - Builds all configurations

### Unix Scripts (Linux/macOS)
- `debug.sh` - Builds debug configuration
- `shared.sh` - Builds shared configuration
- `bundled.sh` - Builds bundled configuration
- `all.sh` - Builds all configurations

## Build Output

Built binaries are placed in the following directory structure:
```
bin/
└── artifact_raylib/
    ├── debug/
    ├── shared/
    └── bundled/
```

Binary names follow the pattern:
```
artifact_raylib-{OS}-{ARCH}-{PROFILE}
```
Example: `artifact_raylib-Windows-x86_64-debug.exe`

## Troubleshooting

### Common Issues

1. **vcpkg Not Found**
    - The build scripts will automatically offer to install vcpkg
    - Alternatively, set the `VCPKG_ROOT` environment variable to your vcpkg installation

2. **CMake Version Error**
```
CMake 3.30 or higher is required
```
- Install the latest CMake version:
    - Windows: Download from [cmake.org](https://cmake.org/download/)
    - Linux: Build from source or use [Kitware's apt repository](https://apt.kitware.com/)
    - macOS: `brew install cmake`

3. **Compiler Requirements**
    - Ensure your compiler supports C++20
    - Update your compiler if necessary:
        - Windows: Install/update Visual Studio 2019/2022
        - Linux: `sudo apt install g++-10` or newer
        - macOS: Update Xcode Command Line Tools

4. **Build Fails with Missing Dependencies**
    - Check internet connection (vcpkg needs to download packages)
    - Try running the build script again
    - Manual vcpkg integration:
```shell script
# Windows
     .\vcpkg\bootstrap-vcpkg.bat

     # Linux/macOS
     ./vcpkg/bootstrap-vcpkg.sh
```

### Getting Help

If you encounter issues:
1. Check the error messages in the build output
2. Verify all prerequisites are correctly installed
3. Ensure you have sufficient disk space
4. Check for system-specific requirements in the error messages

For additional help, please file an issue at:
https://github.com/Drew-Chase/artifact_raylib/issues

When filing an issue, include:
- Your operating system and version
- Build script output including any error messages
- Steps to reproduce the issue

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

For more information, visit the [repository](https://github.com/Drew-Chase/artifact_raylib).