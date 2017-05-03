#include "glTF.h"
#include "parsers/Parsing.h"
#include <catch.hpp>
#include <json.hpp>

using namespace gltfpp;
using nlohmann::json;

TEST_CASE("DataUri_invalid", "[DataUri]") {
	constexpr char http[] = "http://example.com/teapot.glb";
	REQUIRE(!is_data_uri(http));

	constexpr char too_short[] = "dat";
	REQUIRE(!is_data_uri(too_short));
}

TEST_CASE("DataUri_valid", "[DataUri]") {
	auto verify = [](auto &&test_string, unsigned idx) {
		const auto result = is_data_uri(std::forward<decltype(test_string)>(test_string));
		INFO("testing \"" << test_string << "\"");
		REQUIRE(result);
		REQUIRE(*result == test_string + idx);
	};

	constexpr char minimal[] = "data:,";
	verify(minimal, 6);

	constexpr char simple[] = "data:,Hello%2C%20World!";
	verify(simple, 6);

	constexpr char nontrivial[] = "data:text/html,<script>alert('hi');</script>";
	verify(nontrivial, 15);
}
