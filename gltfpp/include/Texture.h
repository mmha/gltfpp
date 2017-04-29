#pragma once
#include "Image.h"
#include "Sampler.h"
#include <boost/hana/define_struct.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct Texture {
			BOOST_HANA_DEFINE_STRUCT(Texture, (Image, image), (Sampler, sampler));
		};
	}	// namespace v1
}	// namespace gltfpp
