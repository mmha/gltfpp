#pragma once
#include "detail/Byte.h"
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct URI : std::vector<byte> {};
		auto parse(URI &uri);
	}	// namespace v1
}	// namespace gltfpp
