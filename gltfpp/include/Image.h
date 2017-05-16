#pragma once
#include <boost/hana/define_struct.hpp>
#include <boost/variant.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct Image {
			BOOST_HANA_DEFINE_STRUCT(Image,
									 (option<std::string>, name),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras));

			boost::variant<std::vector<byte>, BufferView *> data;
			std::string mimeType;
		};
	}	// namespace v1
}	// namespace gltfpp
