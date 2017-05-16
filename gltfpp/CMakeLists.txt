find_package(Boost 1.61)
if(Boost_FOUND)
	set(BOOST_NONCOMPILED_DIR ${Boost_INCLUDE_DIR})
endif()

add_library(gltfpp INTERFACE)
target_link_libraries(gltfpp INTERFACE nlohmann_json microsoft_gsl boost_outcome)
target_include_directories(gltfpp SYSTEM INTERFACE ${BOOST_NONCOMPILED_DIR})
target_include_directories(gltfpp INTERFACE "include")

if(EMSCRIPTEN)
	target_include_directories(gltfpp INTERFACE "include/detail/emscripten")
endif()

