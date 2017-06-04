#include "Asset.h"
#include "common.h"

using namespace gltfpp;

TEST_CASE("Asset_minimal", "[Asset]") {
	common_fixture<Asset> fixture("data/asset_minimal.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_GLTF_RESULT(result);

	auto &asset = fixture.unit_under_test;
	CHECK(asset.version == "2.0");
	CHECK(!asset.copyright.has_value());
	CHECK(!asset.generator.has_value());
	CHECK(!asset.minVersion.has_value());
	CHECK(!asset.extensions.has_value());
	CHECK(!asset.extras.has_value());
}

TEST_CASE("Asset_complete", "[Asset]") {
	nlohmann::json expected_extensions, expected_extras;
	expected_extensions["MY_EXTENSION"] = 42.0;
	expected_extras.push_back("covfefe");

	common_fixture<Asset> fixture("data/asset_complete.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_GLTF_RESULT(result);

	auto &asset = fixture.unit_under_test;
	CHECK(asset.version == "2.0");
	CHECK_GLTF_OPTION(asset.copyright, "2017 (c) Khronos Group");
	CHECK_GLTF_OPTION(asset.generator, "collada2gltf@f356b99aef8868f74877c7ca545f2cd206b9d3b7");
	CHECK_GLTF_OPTION(asset.minVersion, "2.0");
	CHECK_GLTF_OPTION(asset.extensions, expected_extensions);
	CHECK_GLTF_OPTION(asset.extras, expected_extras);
}

TEST_CASE("Asset_missing_version", "[Asset]") {
	common_fixture<Asset> fixture("data/asset_missing_version.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_THAT(result, IsError(gltfpp::gltf_error::key_not_found));
}

TEST_CASE("Asset_version_wrong_type", "[Asset]") {
	common_fixture<Asset> fixture("data/asset_version_wrong_type.json");
	auto result = parse(fixture.unit_under_test)(fixture.ctx);
	CHECK_THAT(result, IsError(gltfpp::gltf_error::type_error));
}
