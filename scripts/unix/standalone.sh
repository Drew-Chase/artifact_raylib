#!/bin/bash
echo "Compiling standalone"
cd ../../
cmake --build bin/obj/standalone --target clean -j 32
cmake --build bin/obj/standalone --target all -j 32