#!/bin/bash
echo "Compiling debug"
cd ../../
cmake --build bin/obj/debug --target clean -j 32
cmake --build bin/obj/debug --target all -j 32