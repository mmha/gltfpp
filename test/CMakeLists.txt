add_executable(gltfpp_test
	Asset.cpp
	Buffer.cpp
	glTF.cpp
	testmain.cpp
)

target_link_libraries(gltfpp_test PRIVATE Catch gltfpp)

add_executable(simple_consumer
	simple_consumer.cpp
)
target_compile_options(simple_consumer PRIVATE -fno-exceptions)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_compile_options(simple_consumer PRIVATE -fmodules-decluse
	-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-non-modular-include-in-module)
endif()
target_link_libraries(simple_consumer PRIVATE gltfpp)
