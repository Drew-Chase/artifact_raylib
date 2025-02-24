cmake_minimum_required(VERSION 3.30)

# Enable vcpkg manifest mode
set(VCPKG_MANIFEST_MODE ON)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg.json")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif ()

project(artifact_raylib)

set(CMAKE_CXX_STANDARD 20)

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
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_PROJECT_NAME}/${PROFILE_NAME}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${CMAKE_PROJECT_NAME}/${PROFILE_NAME}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${PROFILE_NAME}")
set(CMAKE_CACHEFILE_DIR ${PROJECT_SOURCE_DIR}/bin/obj/cmake/${CMAKE_PROJECT_NAME})

if (REMOVE_DEBUG_INFO)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Oz)
endif ()

# I swear to god, if the github workflow fails one more time due to different compiler options, I'm going to force delete this project 😠
if (NOT STRIPPED_VERSION)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if (MSVC)
            # Static linking for MSVC runtime
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
            foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
                if(${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
                endif()
            endforeach()
        else()
            # For GCC/CLang
            set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static-libgcc -static-libstdc++ -static")
        endif()
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static-libgcc -static-libstdc++ -static -lpthread")
    endif()
    # macOS doesn't need these flags and they cause issues, this is because macOS is a precious little flower that doesn't want any of those icky `flags` 😭
endif()

if (PROFILE_NAME STREQUAL "debug")
    set(CMAKE_BUILD_TYPE Debug)
else ()
    set(CMAKE_BUILD_TYPE Release)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        if (MSVC)
            set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,--subsystem,windows")
        endif ()
    endif ()
endif ()

if(WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE winmm)
endif()


# Add automatic linking for vcpkg packages
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib glfw)