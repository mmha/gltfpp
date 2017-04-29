function(add_clang_tidy_check target)
    get_target_property(rel_source_files ${target} SOURCES)

    foreach(f ${rel_source_files})
        get_filename_component(abs_file ${f} ABSOLUTE)
        list(APPEND source_files ${abs_file})
    endforeach()

    add_custom_target(${target}_check)
    add_custom_command(TARGET ${target}_check POST_BUILD
            COMMAND clang-tidy "-p=${PROJECT_BINARY_DIR}"
            "-config='${ARGV1}'"
            "-extra-arg='-fdiagnostics-color=always'"
            "-export-fixes='${CMAKE_CURRENT_BINARY_DIR}/${target}_suggested_fixes.yaml'"
            ${source_files}
            BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/${target}_suggested_fixes.yaml"
    )
endfunction()