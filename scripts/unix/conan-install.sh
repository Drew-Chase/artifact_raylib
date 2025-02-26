#!/bin/bash
echo "Installing Conan Packages..."
conan install . --output-folder=bin/obj/vendors --build=missing