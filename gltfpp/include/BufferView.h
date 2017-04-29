#pragma once
#include "Buffer.h"
#include "Error.h"
#include <boost/hana/define_struct.hpp>
#include <gsl/span>
#include <json.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct BufferView {
			BufferView()
				: byteStride{0} {
			}

			enum Target { ARRAY_BUFFER = 34962, ELEMENT_ARRAY_BUFFER = 34963 };

			BOOST_HANA_DEFINE_STRUCT(BufferView,
									 (int, target),	// TODO enum parsing
									 (option<std::string>, name),
									 (uint8_t, byteStride),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras));
			gsl::span<const byte> span;
			const Buffer *buffer;
		};

		auto parse(BufferView &);
	}	// namespace v1
}	// namespace gltfpp
