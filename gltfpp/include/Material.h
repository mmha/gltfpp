#pragma once
#include "Texture.h"
#include <boost/hana/define_struct.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Material {
			BOOST_HANA_DEFINE_STRUCT(Material,
									 (std::vector<Texture>, textures),
			(option<std::string>, name),
			(option<nlohmann::json>, extensions), 
			(option<nlohmann::json>, exteas), 
			//metallic roughness
			(std::array<float, 3>, emissiveFactor)
									);
		};
	}	// namespace v1
}	// namespace gltfpp
