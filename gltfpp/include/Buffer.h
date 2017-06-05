#pragma once
#include "Error.h"
#include "URI.h"
#include "detail/Byte.h"
#include <boost/hana/define_struct.hpp>
#include <json.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Buffer {
			BOOST_HANA_DEFINE_STRUCT(Buffer,
			                         (option<URI>, uri),
			                         (option<std::string>, name),
			                         (option<nlohmann::json>, extensions),
			                         (option<nlohmann::json>, extras));
		};

		auto parse(Buffer &b) noexcept;
	}    // namespace v1
}    // namespace gltfpp
