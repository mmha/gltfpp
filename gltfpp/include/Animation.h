#pragma once
#include "Error.h"
#include <boost/hana/define_struct.hpp>
#include <json.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct Node;
		struct Animation {
#if 0
			struct Sampler {
				enum Interpolation {LINEAR, STEP, CATMULLROMSPLINE, CUBICSPLINE};
				Sampler()
				: interpolation{Interpolation::LINEAR}
				{}

				BOOST_HANA_DEFINE_STRUCT(Sampler,
										(Accessor *, input),
										(Accessor *, output),
										                                // TODO generic enum parsing
										(option<int>, interpolation),	// TODO Interpolation
										(option<nlohmann::json>, extensions),
										(option<nlohmann::json>, extras));
			};

			struct Channel {
				struct Target {
					enum Path {TRANSLATION, ROTATION, SCALE, WEIGHTS};
					BOOST_HANA_DEFINE_STRUCT(Target, (Node *, node), (Path, path));
				};

				BOOST_HANA_DEFINE_STRUCT(Channel,
										(Sampler *, sampler),
										(Target, node),
										(option<nlohmann::json>, extensions),
										(option<nlohmann::json>, extras)
				);
			};
#endif
			BOOST_HANA_DEFINE_STRUCT(Animation,
									 (std::vector<int>, channels),
									 (std::vector<int>, samplers),
									 (option<std::string>, name),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras));
		};
	}	// namespace v1
}	// namespace gltfpp
