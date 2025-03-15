
function(initialize_vendors)
    find_package(spdlog)
    find_package(nlohmann_json)
    find_package(raylib)


    target_link_libraries(${CMAKE_PROJECT_NAME}
            raylib
            spdlog::spdlog
            nlohmann_json::nlohmann_json
    )
endfunction()