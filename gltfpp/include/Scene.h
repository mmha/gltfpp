#pragma once
#include "Node.h"
#include <boost/hana/define_struct.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Scene {
			BOOST_HANA_DEFINE_STRUCT(Scene, (std::vector<Node>, nodes));
		};
	}    // namespace v1
}    // namespace gltfpp
