#include "Buffer.h"
#include "common.h"
#include "parsers/Buffer.h"

using namespace gltfpp;
using namespace nlohmann;

TEST_CASE("Buffer_minimal", "[Buffer]") {
	common_fixture<Buffer> fixture("data/buffer_minimal.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_GLTF_RESULT(result);

	auto &buffer = fixture.unit_under_test;
	CHECK(!buffer.name.has_value());
	CHECK(!buffer.extras.has_value());
	CHECK(!buffer.extensions.has_value());
	REQUIRE(buffer.uri.has_value());
	REQUIRE(buffer.uri->size() == 50);
}

TEST_CASE("Buffer_complete", "[Buffer]") {
	const auto expected_extensions = R"({
		"KHR_materials_common": {
		"technique": "LAMBERT"
	}
	})"_json;
	const nlohmann::json expected_extras{0, 1, 2, 3};
	constexpr char expected_uri_data[] = "Parsey McParseface";

	common_fixture<Buffer> fixture("data/buffer_complete.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_GLTF_RESULT(result);

	auto &buffer = fixture.unit_under_test;
	CHECK_GLTF_OPTION(buffer.name, "Utah Teapot");
	CHECK_GLTF_OPTION(buffer.extras, expected_extras);
	CHECK_GLTF_OPTION(buffer.extensions, expected_extensions);
	REQUIRE(buffer.uri.has_value());
	REQUIRE(buffer.uri->size() == 18);

	auto str = reinterpret_cast<const char *>(buffer.uri->data());

	const auto matched = std::mismatch(std::begin(expected_uri_data), std::end(expected_uri_data) - 1, str).first ==
						 std::end(expected_uri_data) - 1;
	REQUIRE(matched);
}

TEST_CASE("Buffer_missing_length", "[Buffer]") {
	common_fixture<Asset> fixture("data/buffer_missing_length.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_THAT(result, IsError(gltfpp::gltf_error::key_not_found));
}

TEST_CASE("Buffer_lorem_ipsum", "[Buffer]") {
	constexpr char expected[] =
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor"
		" incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis no"
		"strud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Du"
		"is aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu "
		"fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in"
		" culpa qui officia deserunt mollit anim id est laborum.";

	common_fixture<Buffer> fixture("data/buffer_lorem_ipsum.json");	// has 2 byte padding
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_GLTF_RESULT(result);

	auto &buffer = fixture.unit_under_test;
	REQUIRE(buffer.uri->size() == strlen(expected) + 2);	// TODO Should the padding be removed?
	const auto decoded_correctly = std::equal(buffer.uri->begin(), buffer.uri->end() - 2, expected,
											  [](byte buf, char str) { return to_integer<char>(buf) == str; });
	REQUIRE(decoded_correctly);
}
