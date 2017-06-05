#pragma once
#include "Camera.h"
#include "Mesh.h"
#include "Skin.h"
#include <boost/hana/define_struct.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Node {
			BOOST_HANA_DEFINE_STRUCT(Node,
			                         (std::vector<Node>, nodes),
			                         (std::vector<Mesh>, meshes),
			                         (Skin, skin),
			                         (Camera, camera));
		};
	}    // namespace v1
}    // namespace gltfpp
