#pragma once
#include "BufferView.h"
#include <boost/hana/define_struct.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct Accessor {
			BOOST_HANA_DEFINE_STRUCT(Accessor, (BufferView, bufferView));
		};
	}	// namespace v1
}	// namespace gltfpp
