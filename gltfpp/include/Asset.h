#pragma once
#include "Error.h"
#include <boost/hana/define_struct.hpp>
#include <json.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct Asset {
			BOOST_HANA_DEFINE_STRUCT(Asset,
			                         (option<std::string>, copyright),
			                         (option<std::string>, generator),
			                         (option<std::string>, minVersion),
			                         (std::string, version),

			                         (option<nlohmann::json>, extensions),
			                         (option<nlohmann::json>, extras));
		};
	}    // namespace v1
}    // namespace gltfpp
