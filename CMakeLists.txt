cmake_minimum_required(VERSION 3.8)
project(gltfpp VERSION 1.0)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GenerateClangTidyTarget)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(UNIX OR MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fdiagnostics-color=always")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto -march=native")
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules -fimplicit-module-maps -fbuiltin-module-map -Wdocumentation -Wthread-safety")
endif()

# find_package(Doxygen)
# if(Doxygen_FOUND)
# 	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
# 	if(DOXYGEN_DOT_FOUND)
# 		set(USE_DOT "YES")
# 	else()
# 		set(USE_DOT "NO")
# 	endif()
# 	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
# 	add_custom_target(gltfpp_doc
#                     ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
#                     SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
#                     DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
#                     WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc")
# endif()

add_subdirectory(3rdparty)
add_subdirectory(gltfpp)
enable_testing()
add_subdirectory(test test EXCLUDE_FROM_ALL)
