#pragma once
#include "Enum.h"
#include <boost/hana/define_struct.hpp>

namespace gltfpp {
	inline namespace v1 {
		BETTER_ENUM(CameraType, int, perspective, orthographic)
		struct Camera {
			BOOST_HANA_DEFINE_STRUCT(Camera,
			                         (CameraType, type),
			                         (option<std::string>, name),
			                         (option<nlohmann::json>, orthographic),
			                         (option<nlohmann::json>, perspective),
			                         (option<nlohmann::json>, extras),
			                         (option<nlohmann::json>, extensions));
		};
	}    // namespace v1
}    // namespace gltfpp
