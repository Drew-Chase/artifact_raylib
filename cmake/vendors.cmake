function(initialize_vendors)
    include(FetchContent)
    # Add this near the start of initialize_vendors function
    if(CMAKE_HOST_UNIX)
        set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/obj/unix-deps")
    elseif(CMAKE_HOST_WIN32)
        set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/obj/win-deps")
    else()
        set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/bin/obj/other-deps")
    endif()


    # Disable system paths for find_package
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

    # Try to find packages first
    find_package(spdlog QUIET)
    find_package(nlohmann_json QUIET)
    find_package(fmt QUIET)
    find_package(raylib QUIET)

    # If not found, fetch them
    if(NOT spdlog_FOUND)
        FetchContent_Declare(
                spdlog
                GIT_REPOSITORY https://github.com/gabime/spdlog.git
                GIT_TAG v1.15.1
        )

        # Add these lines to configure spdlog build
        set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
        set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(spdlog)

    endif()

    if(NOT nlohmann_json_FOUND)
        FetchContent_Declare(
                nlohmann_json
                GIT_REPOSITORY https://github.com/nlohmann/json.git
                GIT_TAG v3.11.3
        )
        FetchContent_MakeAvailable(nlohmann_json)
    endif()

    if(NOT raylib_FOUND)
        FetchContent_Declare(
                raylib
                GIT_REPOSITORY https://github.com/raysan5/raylib.git
                GIT_TAG 5.5
        )
        # Configure raylib to build as a static library
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(raylib)
    endif()

    if(NOT fmt_FOUND)
        FetchContent_Declare(
                fmt
                GIT_REPOSITORY https://github.com/fmtlib/fmt.git
                GIT_TAG 11.1.4
        )
        FetchContent_MakeAvailable(fmt)
    endif ()

    target_link_libraries(${CMAKE_PROJECT_NAME}
            raylib
            spdlog::spdlog
            nlohmann_json::nlohmann_json
            fmt::fmt
    )
endfunction()