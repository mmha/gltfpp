#pragma once
#include "Buffer.h"
#include "Error.h"
#include <boost/hana/define_struct.hpp>
#include <gsl/span>
#include <json.hpp>
#include "Enum.h"

namespace gltfpp {
	inline namespace v1 {

		BETTER_ENUM(BufferViewTarget, int32_t, ARRAY_BUFFER = 34962, ELEMENT_ARRAY_BUFFER = 34963)

		struct BufferView {
			BufferView()
				: byteStride{0} {
			}

			BOOST_HANA_DEFINE_STRUCT(BufferView,
									 (option<BufferViewTarget>, target),
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
