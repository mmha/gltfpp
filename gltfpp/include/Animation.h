#pragma once
#include "Error.h"
#include <boost/hana/define_struct.hpp>
#include <json.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct Channel {	// TODO generic enum parsing
			BOOST_HANA_DEFINE_STRUCT(Channel

									 );
		};

		struct AnimationSampler {
			BOOST_HANA_DEFINE_STRUCT(AnimationSampler,
									 (int, input),
									 (int, output),
									 (option<std::string>, interpolation),	// TODO default = linear
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras));
		};

		struct Animation {
			BOOST_HANA_DEFINE_STRUCT(Animation,
									 (std::vector<Channel>, channels),
									 (std::vector<AnimationSampler>, samplers),
									 (option<std::string>, name),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras));
		};
	}	// namespace v1
}	// namespace gltfpp
