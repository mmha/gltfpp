#pragma once
#include "Texture.h"
#include <boost/hana/define_struct.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Material {
			BOOST_HANA_DEFINE_STRUCT(Material(std::vector<Texture>, textures));
		};
	}	// namespace v1
}	// namespace gltfpp
