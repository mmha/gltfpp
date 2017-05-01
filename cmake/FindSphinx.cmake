find_program(SPHINX_EXECUTABLE sphinx-build
    HINTS $ENV{SPHINX_DIR}
    PATH_SUFFIXES bin
)
 
include(FindPackageHandleStandardArgs)
 
find_package_handle_standard_args(Sphinx DEFAULT_MSG SPHINX_EXECUTABLE)
mark_as_advanced(SPHINX_EXECUTABLE)