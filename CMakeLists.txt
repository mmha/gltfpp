cmake_minimum_required(VERSION 3.2)
project(gltfpp VERSION 1.0)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GenerateClangTidyTarget)
include(ExternalProject)

option(GLTFPP_ENABLE_MODULES "Enable clang modules to increase compilation speed - only tested with clang 4.0!" OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(UNIX OR MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fdiagnostics-color=always")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -march=native")
endif()
if(GLTFPP_ENABLE_MODULES AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND NOT EMSCRIPTEN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules")
endif()
if(EMSCRIPTEN)
	option(GLTFPP_WEBASSEMBLY "Generate WebAssembly instead of asm.js" ON)
endif()

find_package(Sphinx)
find_package(Doxygen)
if(Doxygen_FOUND AND Sphinx_FOUND)
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxy")
	if(DOXYGEN_DOT_FOUND)
		set(USE_DOT "YES")
	else()
		set(USE_DOT "NO")
	endif()
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
	add_custom_target(gltfpp_doxygen
                      ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
                      SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
                      DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
                      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxy")

	set(SPHINX_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs/_build")
	set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs/_doctrees")
	set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs/html")

	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/docs/conf.py.in" "${SPHINX_BUILD_DIR}/conf.py" @ONLY)

	add_custom_target(gltfpp_docs
	    ${SPHINX_EXECUTABLE}
	        -q -b html
	        -c "${SPHINX_BUILD_DIR}"
	        -d "${SPHINX_CACHE_DIR}"
	        "${CMAKE_CURRENT_SOURCE_DIR}/docs"
	        "${SPHINX_HTML_DIR}"
	    DEPENDS gltfpp_doxygen
	)
endif()

find_package(WoboqCodebrowser)
if(WoboqCodebrowser_FOUND)
	add_custom_target(gltfpp_codebrowser
                      COMMAND ${WOBOQ_GENERATOR_EXECUTABLE}
                      	-b "${CMAKE_CURRENT_BINARY_DIR}"
                      	-a -o "${CMAKE_CURRENT_BINARY_DIR}/codebrowser/browser"
                      	-p "${PROJECT_NAME}:${CMAKE_CURRENT_SOURCE_DIR}"
                      COMMAND ${WOBOQ_INDEX_GENERATOR_EXECUTABLE}
                      	"${CMAKE_CURRENT_BINARY_DIR}/codebrowser/browser"
                      COMMAND ${CMAKE_COMMAND}
                      	-E copy_directory ${WOBOQ_DATA_DIR} "${CMAKE_CURRENT_BINARY_DIR}/codebrowser/data"
    )
endif()

add_subdirectory(3rdparty)
add_subdirectory(gltfpp)

option(GLTFPP_BUILD_TESTS "Enables the test suite targets" OFF)
if(GLTFPP_BUILD_TESTS)
	enable_testing()
	add_subdirectory(test test EXCLUDE_FROM_ALL)
endif()
