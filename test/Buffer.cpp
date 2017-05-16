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
	REQUIRE(buffer.uri);
	REQUIRE(buffer.extras.empty());
	REQUIRE(buffer.extensions.empty());
	REQUIRE(buffer.uri->size() == 50);
}

TEST_CASE("Buffer_Complete", "[Buffer]") {
	auto input = R"({
		"uri": "data:text/plain;base64,UGFyc2V5IE1jUGFyc2VmYWNl",
		"byteLength": 18,
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
	REQUIRE(buffer.extras.get() == extra);
	REQUIRE(buffer.extensions.get() == extension);
	REQUIRE(buffer.uri->size() == 18);

	auto str = reinterpret_cast<const char *>(buffer.uri->data());
	constexpr char expected[] = "Parsey McParseface";
	const auto matched =
		std::mismatch(std::begin(expected), std::end(expected) - 1, str).first == std::end(expected) - 1;
	REQUIRE(matched);
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

TEST_CASE("Buffer_WithData", "[Buffer]") {
	const nlohmann::json input{
		{
			"uri",
			"text/plain;base64,TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc"
			"2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIGluY2lkaWR1bnQgdXQgbGFib3JlIGV0IGRv"
			"bG9yZSBtYWduYSBhbGlxdWEuIFV0IGVuaW0gYWQgbWluaW0gdmVuaWFtLCBxdWlzIG5vc3RydWQgZXh"
			"lcmNpdGF0aW9uIHVsbGFtY28gbGFib3JpcyBuaXNpIHV0IGFsaXF1aXAgZXggZWEgY29tbW9kbyBjb2"
			"5zZXF1YXQuIER1aXMgYXV0ZSBpcnVyZSBkb2xvciBpbiByZXByZWhlbmRlcml0IGluIHZvbHVwdGF0Z"
			"SB2ZWxpdCBlc3NlIGNpbGx1bSBkb2xvcmUgZXUgZnVnaWF0IG51bGxhIHBhcmlhdHVyLiBFeGNlcHRl"
			"dXIgc2ludCBvY2NhZWNhdCBjdXBpZGF0YXQgbm9uIHByb2lkZW50LCBzdW50IGluIGN1bHBhIHF1aSB"
			"vZmZpY2lhIGRlc2VydW50IG1vbGxpdCBhbmltIGlkIGVzdCBsYWJvcnVtLg=="	// <-- 2 byte padding
		},
		{"byteLength", 445}};

	constexpr char expected[] =
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
		" incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis no"
		"strud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Du"
		"is aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu "
		"fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in"
		" culpa qui officia deserunt mollit anim id est laborum.";

	glTF gltf;
	Buffer buffer;

	auto success = parse(buffer)({&gltf, &input});
	if(!success) {
		FAIL("Parsing failed - Error: " << success.error().message());
	}

	REQUIRE(buffer.uri->size() == strlen(expected) + 2);	// TODO Should the padding be removed?
	const auto decoded_correctly = std::equal(buffer.uri->begin(), buffer.uri->end() - 2, expected,
											  [](byte buf, char str) { return to_integer<char>(buf) == str; });
	REQUIRE(decoded_correctly);
}
