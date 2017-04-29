#include "Buffer.h"
#include "Error.h"
#include "glTF.h"
#include <catch.hpp>
#include <json.hpp>

using namespace gltfpp;
using nlohmann::json;

namespace {
	const auto minimalAsset = R"({
		"version": "2.0"
	})"_json;
}

TEST_CASE("Asset_Minimal", "[Asset]") {
	glTF g;
	ParseContext ctx{&g, &minimalAsset};

	Asset a;
	auto success = parse(a)(ctx);
	REQUIRE(success);
	REQUIRE(a.version == "2.0");
}
