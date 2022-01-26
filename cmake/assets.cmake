add_custom_target(ass02_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_FOLDER} ${BINARY_OUT_DIR}/
)