#pragma once
#include "Error.h"
#include "glTF.h"
#include <catch.hpp>
#include <fstream>
#include <json.hpp>
#include <string>

inline std::string load_file(const std::string &filename) {
	INFO("loading file " << filename);
	std::ifstream is(filename);
	REQUIRE(is.good());
	std::string str(std::istreambuf_iterator<char>(is), {});
	INFO(str);
	REQUIRE(is.good());
	return str;
}

template <typename UUT>
struct common_fixture {
	common_fixture(const std::string &filename)
	    : input_json(nlohmann::json::parse(load_file(filename)))
	    , ctx{&root, &input_json} {
	}

	nlohmann::json input_json;
	gltfpp::glTF root;
	gltfpp::ParseContext ctx;
	UUT unit_under_test;
};

class ResultError : public Catch::MatcherBase<gltfpp::gltf_result<gltfpp::ParseContext>> {
	gltfpp::gltf_error expected_error;

	public:
	explicit ResultError(gltfpp::gltf_error err)
	    : expected_error(err) {
	}

	// Performs the test for this matcher
	bool match(gltfpp::gltf_result<gltfpp::ParseContext> const &res) const override {
		return res.has_error() && res.error() == expected_error;
	}

	// Produces a string describing what this matcher does. It should
	// include any provided data (the begin/ end in this case) and
	// be written as if it were stating a fact (in the output it will be
	// preceded by the value under test).
	std::string describe() const override {
		std::ostringstream ss;
		ss << "is an error of type " << expected_error.message();
		return ss.str();
	}
};

namespace gltfpp {
	inline std::ostream &operator<<(std::ostream &os, const gltfpp::ParseContext &ctx) {
		return os << "ParseContext{" << ctx.root << ", " << ctx.json << '}';
	}
}    // namespace gltfpp

// The builder function
inline ResultError IsError(gltfpp::gltf_error err) {
	return ResultError(err);
}

#define CHECK_GLTF_RESULT(res)                \
	INFO((res ? "" : res.error().message())); \
	CHECK(res)

#define REQUIRE_GLTF_RESULT(res)              \
	INFO((res ? "" : res.error().message())); \
	REQUIRE(res)

#define CHECK_GLTF_OPTION(opt, expected) \
	CHECK(opt.has_value());              \
	CHECK((opt.has_value() ? opt.value() == expected : false))
