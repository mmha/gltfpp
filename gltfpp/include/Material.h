#pragma once
#include "Texture.h"
#include <boost/hana/define_struct.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Material {
			struct PBRMetalllicRoughness {
				BOOST_HANA_DEFINE_STRUCT(PBRMetalllicRoughness,
				                         (std::array<double, 3>, baseColorFactor),
				                         (Texture, baseColorTexture),
				                         (double, metallicFactor),
				                         (double, roughnessFactor),
				                         (Texture, metallicRoughnessTexture));
			};

			BOOST_HANA_DEFINE_STRUCT(Material,
			                         (std::vector<Texture>, textures),
			                         (option<std::string>, name),
			                         (option<nlohmann::json>, extensions),
			                         (option<nlohmann::json>, extras),
			                         (PBRMetalllicRoughness, pbrMetallicRoughness),
			                         (std::array<double, 3>, emissiveFactor));
		};
	}    // namespace v1
}    // namespace gltfpp
