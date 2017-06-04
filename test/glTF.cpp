#include "gltfpp.h"
#include "common.h"

using namespace gltfpp;
using nlohmann::json;

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
	REQUIRE_GLTF_RESULT(success);
	CHECK(target.asset.version == "2.0");
	CHECK_GLTF_OPTION(target.asset.generator, "collada2gltf@f356b99aef8868f74877c7ca545f2cd206b9d3b7");
	CHECK_GLTF_OPTION(target.asset.copyright, "2017 (c) Khronos Group");
}

TEST_CASE("glTF_Buffer", "[glTF]") {
	glTF target;
	auto source = minimalglTF;
	json minimalBuffer{"byteLength", 42};
	source["buffer"] = {minimalBuffer, minimalBuffer, minimalBuffer};

	const auto success = from_json(source, target);
	REQUIRE_GLTF_RESULT(success);
}

TEST_CASE("glTF_BufferView", "[glTF]") {
	glTF target;
	auto source = minimalglTF;
	json minimalBuffer{"byteLength", 42};
	source["buffer"] = {minimalBuffer, minimalBuffer, minimalBuffer};

	json minimalBufferView{{"buffer", 0}, {"byteOffset", 0}, {"byteLength", 1}, {"target", "ARRAY_BUFFER"}};

	source["bufferViews"] = {minimalBufferView, minimalBufferView};

	const auto success = from_json(source, target);
	REQUIRE_GLTF_RESULT(success);
	REQUIRE(target.bufferViews.has_value());
	REQUIRE(target.bufferViews->size() == 2);
	REQUIRE(target.bufferViews.get()[0].target);
	const bool enum_is_array_buffer = target.bufferViews.get()[0].target.get() == +BufferViewTarget::ARRAY_BUFFER;
	REQUIRE(enum_is_array_buffer);
}
