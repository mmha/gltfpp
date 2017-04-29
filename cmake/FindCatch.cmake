find_path(CATCH_INCLUDE_DIR NAMES catch.hpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Catch REQUIRED_VARS CATCH_INCLUDE_DIR)

add_library(Catch::Catch INTERFACE IMPORTED)
set_target_properties(Catch::Catch PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CATCH_INCLUDE_DIR})

mark_as_advanced(CATCH_INCLUDE_DIR)