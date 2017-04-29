#include "glTF.h"
#include <catch.hpp>

using namespace gltfpp;
using nlohmann::json;
using namespace std::literals;

namespace {
	const auto minimalglTF = R"({
		"asset": {
			"version": "2.0",
			"generator": "collada2gltf@f356b99aef8868f74877c7ca545f2cd206b9d3b7",
			"copyright": "2017 (c) Khronos Group"
		}
	})"_json;
}

TEST_CASE("glTF_Minimal", "[glTF]") {
	glTF target;
	const auto success = from_json(minimalglTF, target);
	REQUIRE(success);
	REQUIRE(target.asset.version == "2.0");
	REQUIRE(target.asset.generator.get() == "collada2gltf@f356b99aef8868f74877c7ca545f2cd206b9d3b7");
	REQUIRE(target.asset.copyright.get() == "2017 (c) Khronos Group");
}

TEST_CASE("glTF_Buffer", "[glTF]") {
	glTF target;
	auto source = minimalglTF;
	json minimalBuffer{"byteLength", 42};
	source["buffer"] = {minimalBuffer, minimalBuffer, minimalBuffer};

	const auto success = from_json(source, target);
	REQUIRE(success);
}

TEST_CASE("glTF_BufferView", "[glTF]") {
}
