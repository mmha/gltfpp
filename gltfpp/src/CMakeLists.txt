find_package(GSL REQUIRED)

add_library(gltfpp
	Buffer.cpp
	glTF.cpp
)

target_link_libraries(gltfpp PUBLIC nlohmann_json microsoft_gsl boost_outcome)
target_include_directories(gltfpp PUBLIC "../include")
target_compile_options(gltfpp PRIVATE -fno-exceptions)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_compile_options(gltfpp PRIVATE -fmodules-decluse -fmodule-name=glTF
	-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic)
endif()
#cotire(gltfpp)
add_clang_tidy_check(gltfpp)

install(TARGETS gltfpp
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
