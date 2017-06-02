#pragma once
#include <boost/hana/define_struct.hpp>
#include <vector>
#include "Material.h"
#include "Accessor.h"

namespace gltfpp {
	inline namespace v1 {
		BETTER_ENUM(PrimitiveMode, int,
			POINTS = 0,
			LINES = 1,
			LINE_LOOP = 2,
			LINE_STRIP = 3,
			TRIANGLES = 4,
			TRIANGLE_STRIP = 5,
			TRIANGLE_FAN = 6)

		struct Mesh {
			struct Primitive {
				BOOST_HANA_DEFINE_STRUCT(Primitive,
				//(std::unordered_map<std::string, int>, attributes),
				(Accessor *, indices),
				(Material *, material),
				(PrimitiveMode, mode),
				//(???, targets),
				(nlohmann::json, extensions),
				(nlohmann::json, extras)
				);
			};
			BOOST_HANA_DEFINE_STRUCT(Mesh);
		};
		
		auto parse(Mesh::Primitive &p) noexcept;
	}	// namespace v1
}	// namespace gltfpp
