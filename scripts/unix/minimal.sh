#!/bin/bash
echo "Compiling minimal"
cd ../../
cmake --build bin/obj/minimal --target clean -j 32
cmake --build bin/obj/minimal --target all -j 32