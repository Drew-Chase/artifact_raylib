cmake_minimum_required(VERSION 3.22)
project(artifact_raylib)
set(CMAKE_CXX_STANDARD 23)
add_executable(asset_bundle_tool main.cpp)

set(CMAKE_CACHEFILE_DIR /bin/obj/cmake/asset_bundle_tool)

# Download and install deps
include(FetchContent)
# Add this near the start of initialize_vendors function
if (CMAKE_HOST_UNIX)
    set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/obj/unix-deps")
elseif (CMAKE_HOST_WIN32)
    set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/obj/win-deps")
else ()
    set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/obj/other-deps")
endif ()


# Disable system paths for find_package
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Try to find packages first
find_package(spdlog QUIET)
find_package(fmt QUIET)
find_package(raylib QUIET)
find_package(cclip QUIET)
find_package(color_codes QUIET)

# If not found, fetch them
if (NOT spdlog_FOUND)
    FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG v1.15.1
    )

    # Add these lines to configure spdlog build
    set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
    set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(spdlog)

endif ()
if (NOT cclip_FOUND)
    FetchContent_Declare(
            cclip
            GIT_REPOSITORY https://github.com/Drew-Chase/cclip.git
            GIT_TAG 0.1.0
    )

    FetchContent_MakeAvailable(cclip)
endif ()
if (NOT color_codes_FOUND)
    FetchContent_Declare(
            color_codes
            GIT_REPOSITORY https://github.com/Drew-Chase/ANSIConsoleColors.git
            GIT_TAG 8209b602737e0e06741e4230c7ba4e9f913999e1
    )

    FetchContent_MakeAvailable(color_codes)
endif ()

if (NOT raylib_FOUND)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.5
    )
    # Configure raylib to build as a static library
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif ()

if (NOT fmt_FOUND)
    FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 11.1.4
    )
    FetchContent_MakeAvailable(fmt)
endif ()

target_link_libraries(asset_bundle_tool
        raylib
        spdlog::spdlog
        cclip
        color_codes
        fmt::fmt
)