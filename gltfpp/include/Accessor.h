#pragma once
#include "BufferView.h"
#include "Enum.h"
#include "Error.h"
#include "parsers/Parsing.h"
#include <boost/hana/define_struct.hpp>
#include <gsl/span>

namespace gltfpp {
	inline namespace v1 {
		BETTER_ENUM(AccessorComponentType,
					int,
					BYTE = 5120,
					UNSIGNED_BYTE = 5121,
					SHORT = 5122,
					UNSIGNED_SHORT = 5123,
					UNSIGNED_INT = 5125,
					FLOAT = 5126)

		BETTER_ENUM(AccessorType, int, SCALAR, VEC2, VEC3, VEC4, MAT2, MAT3, MAT4)

		constexpr auto AccessorTypeComponentCount =
			boost::hana::make_map(boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::SCALAR>, 1),
								  boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::VEC2>, 2),
								  boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::VEC3>, 3),
								  boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::VEC4>, 4),
								  boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::MAT2>, 4),
								  boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::MAT3>, 9),
								  boost::hana::make_pair(boost::hana::int_c<(int)AccessorType::MAT4>, 16));

		struct Accessor {
			BOOST_HANA_DEFINE_STRUCT(Accessor,
									 (bool, normalized),
									 (std::vector<double>, min),
									 (std::vector<double>, max),
									 (option<std::string>, name),
									 (option<nlohmann::json>, sparse),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras),
									 (ptrdiff_t, byteOffset),
									 (size_t, count),
									 (AccessorComponentType, componentType));
			BufferView const *bufferView;
		};

		auto parse(Accessor &) noexcept;
	}	// namespace v1
}	// namespace gltfpp
