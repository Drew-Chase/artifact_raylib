cmake_minimum_required(VERSION 3.22)
project(artifact_raylib)
set(CMAKE_CXX_STANDARD 23)

include(cmake/assets.cmake)
include(cmake/vendors.cmake)
include(cmake/gcc.cmake)
include(cmake/clang.cmake)
include(cmake/msvc.cmake)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        ${SOURCES}
        ${HEADERS}
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

# Add -DPROFILE_NAME=profile_name_here to the compiler
option(PROFILE_NAME "Name of the profile to use" "debug") # Default is debug
# Add -DREMOVE_DEBUG_INFO=ON/OFF to the compiler
option(REMOVE_DEBUG_INFO "Remove debug information from the build" OFF) # Default is OFF
# Add -DSTRIPPED_VERSION=ON/OFF to the compiler
option(STRIPPED_VERSION "Create a stripped version of the build without certain flags" OFF) # Default is OFF

# Setting up the bin and obj directories as the good lord intended.
# Non of that `cmake-build-*` crap.
set(RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME}/${PROFILE_NAME}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${CMAKE_PROJECT_NAME}/${PROFILE_NAME}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${PROFILE_NAME}")
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin/obj/${PROFILE_NAME}")
set(CMAKE_CACHEFILE_DIR ${PROJECT_SOURCE_DIR}/bin/obj/cmake/${CMAKE_PROJECT_NAME})
if (WIN32)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE "resources/resources.rc")
endif ()

build_gcc()
build_clang()
build_msvc()

copy_used_assets()
initialize_vendors()