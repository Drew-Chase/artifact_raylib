function(copy_assets)
    set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
    set(ASSETS_OUTPUT_DIR "${RUNTIME_OUTPUT_DIRECTORY}/game")

    file(REMOVE_RECURSE "${ASSETS_OUTPUT_DIR}")

    file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "include/*.h" "main.cpp")
    set(USED_ASSETS "")

    foreach (SOURCE_FILE ${SOURCE_FILES})
        file(READ ${SOURCE_FILE} FILE_CONTENTS)

        string(REGEX MATCHALL "LoadTexture\\([\"']([^\"']+)[\"']\\)" TEXTURE_MATCHES "${FILE_CONTENTS}")
        foreach (MATCH ${TEXTURE_MATCHES})
            string(REGEX REPLACE "LoadTexture\\([\"']([^\"']+)[\"']\\)" "\\1" ASSET_PATH "${MATCH}")

            string(REGEX REPLACE "^game/" "" RELATIVE_PATH "${ASSET_PATH}")

            list(APPEND USED_ASSETS "${RELATIVE_PATH}")
            message("Found texture resource in source file: ${SOURCE_FILE} - ${RELATIVE_PATH}")
        endforeach ()

        string(REGEX MATCHALL "LoadImage\\([\"']([^\"']+)[\"']\\)" IMAGE_MATCHES "${FILE_CONTENTS}")
        foreach (MATCH ${IMAGE_MATCHES})
            string(REGEX REPLACE "LoadImage\\([\"']([^\"']+)[\"']\\)" "\\1" ASSET_PATH "${MATCH}")
            string(REGEX REPLACE "^game/" "" RELATIVE_PATH "${ASSET_PATH}")
            list(APPEND USED_ASSETS "${RELATIVE_PATH}")
            message("Found image resource in source file: ${SOURCE_FILE} - ${RELATIVE_PATH}")
        endforeach ()

        string(REGEX MATCHALL "LoadSound\\([\"']([^\"']+)[\"']\\)" SOUND_MATCHES "${FILE_CONTENTS}")
        foreach (MATCH ${SOUND_MATCHES})
            string(REGEX REPLACE "LoadSound\\([\"']([^\"']+)[\"']\\)" "\\1" ASSET_PATH "${MATCH}")
            string(REGEX REPLACE "^game/" "" RELATIVE_PATH "${ASSET_PATH}")
            list(APPEND USED_ASSETS "${RELATIVE_PATH}")
            message("Found sound resource in source file: ${SOURCE_FILE} - ${RELATIVE_PATH}")
        endforeach ()

        string(REGEX MATCHALL "LoadMusic\\([\"']([^\"']+)[\"']\\)" MUSIC_MATCHES "${FILE_CONTENTS}")
        foreach (MATCH ${MUSIC_MATCHES})
            string(REGEX REPLACE "LoadMusic\\([\"']([^\"']+)[\"']\\)" "\\1" ASSET_PATH "${MATCH}")
            string(REGEX REPLACE "^game/" "" RELATIVE_PATH "${ASSET_PATH}")
            list(APPEND USED_ASSETS "${RELATIVE_PATH}")
        endforeach ()

        string(REGEX MATCHALL "set_background\\([\"']([^\"']+)[\"']\\)" BACKGROUND_MATCHES "${FILE_CONTENTS}")
        foreach (MATCH ${BACKGROUND_MATCHES})
            string(REGEX REPLACE "set_background\\([\"']([^\"']+)[\"']\\)" "\\1" ASSET_PATH "${MATCH}")
            string(REGEX REPLACE "^game/" "" RELATIVE_PATH "${ASSET_PATH}")
            list(APPEND USED_ASSETS "${RELATIVE_PATH}")
            message("Found background resource in source file: ${SOURCE_FILE} - ${RELATIVE_PATH}")
        endforeach ()
    endforeach ()

    list(REMOVE_DUPLICATES USED_ASSETS)

    file(MAKE_DIRECTORY "${ASSETS_OUTPUT_DIR}")

    foreach (RELATIVE_PATH ${USED_ASSETS})
        set(SOURCE_ASSET_PATH "${ASSETS_SOURCE_DIR}/${RELATIVE_PATH}")
        set(DEST_ASSET_PATH "${ASSETS_OUTPUT_DIR}/${RELATIVE_PATH}")

        get_filename_component(DEST_ASSET_DIR "${DEST_ASSET_PATH}" DIRECTORY)

        file(MAKE_DIRECTORY "${DEST_ASSET_DIR}")

        if (EXISTS "${SOURCE_ASSET_PATH}")
            file(COPY "${SOURCE_ASSET_PATH}" DESTINATION "${DEST_ASSET_DIR}")
            message(STATUS "Copying used asset: ${RELATIVE_PATH}")
        else ()
            message(WARNING "Asset referenced but not found: ${SOURCE_ASSET_PATH}")
        endif ()
    endforeach ()
endfunction()