#pragma once
#include "Error.h"
#include "detail/Byte.h"
#include <json.hpp>
#include <vector>
#include <boost/hana/define_struct.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct Buffer {
			std::vector<byte> &operator*();
			const std::vector<byte> &operator*() const;
			std::vector<byte> *operator->();
			const std::vector<byte> *operator->() const;
			std::vector<byte> &get();
			const std::vector<byte> &get() const;

			BOOST_HANA_DEFINE_STRUCT(Buffer,
				(option<std::string>, uri),
				(option<std::string>, name),
				(option<nlohmann::json>, extensions),
				(option<nlohmann::json>, extras)
			);
			std::vector<byte> data;
		};

		auto parse(Buffer &b);
	}	// namespace v1
}	// namespace gltfpp
