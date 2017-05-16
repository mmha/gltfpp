#include "parsers/URI.h"
#include "glTF.h"
#include <catch.hpp>
#include <json.hpp>

using namespace gltfpp;
using namespace gltfpp::detail;
using nlohmann::json;

TEST_CASE("DataUri_invalid", "[DataUri]") {
	constexpr char http[] = "http://example.com/teapot.glb";
	REQUIRE(!parse_data_uri(std::begin(http), std::end(http)));

	constexpr char too_short[] = "dat";
	REQUIRE(!parse_data_uri(std::begin(too_short), std::end(too_short)));
}

TEST_CASE("DataUri_valid", "[DataUri]") {
	auto verify = [](auto &&test_string) {
		const auto begin = std::begin(std::forward<decltype(test_string)>(test_string));
		const auto end = std::end(std::forward<decltype(test_string)>(test_string));
		const auto result = parse_data_uri(begin, end);
		INFO("testing \"" << test_string << "\"");
		INFO(result.data_begin - begin << " " << result.data_end - begin);
		REQUIRE(result);
		return result;
	};

	constexpr char minimal[] = "data:,";
	verify(minimal);

	constexpr char simple[] = "data:,Hello%2C%20World!";
	verify(simple);

	constexpr char nontrivial[] = "data:text/html,<script>alert('hi');</script>";
	verify(nontrivial);

	constexpr char nontrivial2[] = "data:text/plain;base64,UGFyc2V5IE1jUGFyc2VmYWNl";
	{
		const auto result = verify(nontrivial2);
		REQUIRE(result.data_begin == nontrivial2 + 23);
		REQUIRE(result.data_end == std::end(nontrivial2));
		REQUIRE(result.mime_begin == nontrivial2 + 5);
		REQUIRE(result.mime_end == nontrivial2 + 5 + 10);
	}
}
