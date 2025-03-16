# asset_copier.cmake
function(copy_used_assets)
    set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
    set(ASSETS_OUTPUT_DIR "${RUNTIME_OUTPUT_DIRECTORY}/game")

    # Create output directory if it doesn't exist
    file(MAKE_DIRECTORY ${ASSETS_OUTPUT_DIR})

    # Get all source files
    file(GLOB_RECURSE SOURCE_FILES
            "${CMAKE_SOURCE_DIR}/src/*.cpp"
            "${CMAKE_SOURCE_DIR}/src/*.h"
            "${CMAKE_SOURCE_DIR}/include/*.cpp"
            "${CMAKE_SOURCE_DIR}/include/*.h"
    )

    # Initialize set of assets to copy
    set(ASSETS_TO_COPY "")

    # Process each source file
    foreach(SOURCE_FILE ${SOURCE_FILES})
        # Read file content line by line
        file(STRINGS "${SOURCE_FILE}" FILE_LINES)

        foreach(LINE ${FILE_LINES})
            # Extract asset paths using regex
            string(REGEX MATCHALL "\"game/[^\"]+\"" MATCHES "${LINE}")

            foreach(MATCH ${MATCHES})
                # Remove quotes
                string(REGEX REPLACE "\"(.*)\"" "\\1" ASSET_PATH "${MATCH}")

                # Check if path contains %d formatting
                if("${ASSET_PATH}" MATCHES "%d")
                    # Look for the first number after the path string
                    # This handles function calls like SpriteSheet idle_sheet("game/texture/entities/player/idle%d.png", 9, 8);
                    string(REGEX MATCH "\"${ASSET_PATH}\"[^0-9]*([0-9]+)" COUNT_MATCH "${LINE}")

                    if(COUNT_MATCH)
                        # Extract the actual number
                        string(REGEX REPLACE ".*\"${ASSET_PATH}\"[^0-9]*([0-9]+).*" "\\1" COUNT "${LINE}")
                        message(STATUS "Found pattern with count: ${ASSET_PATH}, Count: ${COUNT}")

                        # Generate paths for each numbered asset
                        math(EXPR COUNT_MAX "${COUNT}")
                        foreach(NUM RANGE 1 ${COUNT_MAX})
                            if(NUM LESS 10)
                                set(NUM_STR "0${NUM}")
                            else()
                                set(NUM_STR "${NUM}")
                            endif()

                            string(REPLACE "%d" "${NUM_STR}" NUMBERED_PATH "${ASSET_PATH}")

                            # Check if asset exists (strip 'game/' prefix)
                            string(SUBSTRING "${NUMBERED_PATH}" 5 -1 RELATIVE_PATH)
                            set(FULL_SOURCE_PATH "${ASSETS_SOURCE_DIR}/${RELATIVE_PATH}")

                            if(EXISTS "${FULL_SOURCE_PATH}")
                                message(STATUS "Found numbered asset: ${NUMBERED_PATH}")
                                list(APPEND ASSETS_TO_COPY "${NUMBERED_PATH}")
                            else()
                                message(WARNING "Numbered asset not found: ${NUMBERED_PATH}")
                            endif()
                        endforeach()
                    else()
                        message(WARNING "Found %d in path but couldn't extract count: ${LINE}")
                    endif()
                else()
                    # Check if regular asset exists (strip 'game/' prefix)
                    string(SUBSTRING "${ASSET_PATH}" 5 -1 RELATIVE_PATH)
                    set(FULL_SOURCE_PATH "${ASSETS_SOURCE_DIR}/${RELATIVE_PATH}")

                    if(EXISTS "${FULL_SOURCE_PATH}")
                        message(STATUS "Found asset: ${ASSET_PATH}")
                        list(APPEND ASSETS_TO_COPY "${ASSET_PATH}")
                    else()
                        message(WARNING "Asset not found: ${ASSET_PATH}")
                    endif()
                endif()
            endforeach()
        endforeach()
    endforeach()

    # Remove duplicates
    if(ASSETS_TO_COPY)
        list(REMOVE_DUPLICATES ASSETS_TO_COPY)
    endif()

    # Copy each asset
    foreach(ASSET_PATH ${ASSETS_TO_COPY})
        string(SUBSTRING "${ASSET_PATH}" 5 -1 RELATIVE_PATH)
        set(SOURCE_FILE "${ASSETS_SOURCE_DIR}/${RELATIVE_PATH}")
        set(DEST_FILE "${ASSETS_OUTPUT_DIR}/${RELATIVE_PATH}")

        # Create destination directory
        get_filename_component(DEST_DIR "${DEST_FILE}" DIRECTORY)
        file(MAKE_DIRECTORY "${DEST_DIR}")

        # Copy the file
        message(STATUS "Copying asset: ${ASSET_PATH}")
        file(COPY "${SOURCE_FILE}" DESTINATION "${DEST_DIR}")
    endforeach()
endfunction()