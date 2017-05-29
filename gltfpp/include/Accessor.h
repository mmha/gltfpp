#pragma once
#include "BufferView.h"
#include "Error.h"
#include "parsers/Parsing.h"
#include <boost/hana/define_struct.hpp>
#include <gsl/span>

namespace gltfpp {
	inline namespace v1 {
		template <typename T>
		struct Accessor {
			enum ComponentType {

			};

			enum Type { SCALAR, VEC2, VEC3, VEC4, MAT2, MAT3, MAT4 };

			BOOST_HANA_DEFINE_STRUCT(Accessor,
									 (BufferView *, bufferView),
									 (bool, normalized),
									 (std::vector<double>, min),
									 (std::vector<double>, max),
									 (option<std::string>, name),
									 (option<nlohmann::json>, sparse),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras)); /*
																	   (ptrdiff_t, byteOffset),
																	   (size_t, count),
																	   (ComponentType, componentType),
																	   */
			gsl::span<T> elements;
		};

		template <typename T>
		auto parse(Accessor<T> &) -> gltf_result<ParseContext>;
	}	// namespace v1
}	// namespace gltfpp
