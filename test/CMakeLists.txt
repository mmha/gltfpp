include(ParseAndAddCatchTests)

add_executable(gltfpp_test
	Asset.cpp
	Buffer.cpp
	glTF.cpp
	URI.cpp
	testmain.cpp
)
ParseAndAddCatchTests(gltfpp_test)
target_link_libraries(gltfpp_test PRIVATE Catch gltfpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(simple_consumer
	simple_consumer.cpp
)
#target_compile_options(simple_consumer PRIVATE -fno-exceptions)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_compile_options(simple_consumer PRIVATE
	-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-non-modular-include-in-module)
	if(GLTFPP_ENABLE_MODULES)
		target_compile_options(simple_consumer PRIVATE -fmodules-decluse)
	endif()
endif()
target_link_libraries(simple_consumer PRIVATE gltfpp)

find_package(Sanitizers)
if(HAS_Address_SANITIZER AND HAS_Fuzzer_SANITIZER)
	add_executable(fuzz fuzzing.cpp)
	target_link_libraries(fuzz PUBLIC gltfpp Sanitizer::Fuzzer Sanitizer::Address)
endif()
