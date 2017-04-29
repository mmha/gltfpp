#include "Buffer.h"
#include "Error.h"
#include "glTF.h"
#include "parsers/Buffer.h"
#include <catch.hpp>
#include <json.hpp>

using namespace gltfpp;
using nlohmann::json;

TEST_CASE("Buffer_Minimal", "[Buffer]") {
	const auto input = R"({
		"byteLength": 50
	})"_json;

	glTF gltf;
	Buffer buffer;
	auto success = parse(buffer)({&gltf, &input});
	REQUIRE(success);

	REQUIRE(!buffer.name);
	REQUIRE(!buffer.uri);
	REQUIRE(buffer.extras.empty());
	REQUIRE(buffer.extensions.empty());
	REQUIRE(buffer->size() == 50);
}

TEST_CASE("Buffer_Complete", "[Buffer]") {
	auto input = R"({
		"uri": "https://example.com/teapot.bin",
		"byteLength": 123,
		"name": "Utah Teapot",
		"extras": ["I", "am", "an", "array"]
	})"_json;

	const json extension{{"KHR_materials_common", {"technique", "LAMBERT"}}};
	const json extra{0, 1, 2, 3};

	input["extensions"] = extension;
	input["extras"] = extra;

	glTF gltf;
	Buffer buffer;
	auto success = parse(buffer)({&gltf, &input});
	REQUIRE(success);

	REQUIRE(buffer.name);
	REQUIRE(buffer.name.get() == "Utah Teapot");
	REQUIRE(buffer.uri);
	REQUIRE(buffer.uri.get() == "https://example.com/teapot.bin");
	REQUIRE(buffer.extras.get() == extra);
	REQUIRE(buffer.extensions.get() == extension);
	REQUIRE(buffer->size() == 123);
}

TEST_CASE("Buffer_MissingLength", "[Buffer]") {
	auto input = R"({
		"uri": "https://example.com/teapot.bin",
		"name": "Utah Teapot",
		"extras": ["I", "am", "an", "array"]
	})"_json;

	const json extension{{"KHR_materials_common", {"technique", "LAMBERT"}}};
	const json extra{0, 1, 2, 3};

	input["extensions"] = extension;
	input["extras"] = extra;

	glTF gltf;
	Buffer buffer;
	auto result = parse(buffer)({&gltf, &input});

	REQUIRE(result.has_error());
	REQUIRE(result.get_error() == gltf_error::key_not_found);
}
