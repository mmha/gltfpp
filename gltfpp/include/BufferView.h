#pragma once
#include "Buffer.h"
#include "Enum.h"
#include "Error.h"
#include "detail/Defaulted.h"
#include <boost/hana/define_struct.hpp>
#include <gsl/span>
#include <json.hpp>

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
			                         (defaulted<uint8_t>, byteStride),
			                         (option<nlohmann::json>, extensions),
			                         (option<nlohmann::json>, extras));
			gsl::span<byte const> span;
			Buffer const *buffer;
		};

		auto parse(BufferView &) noexcept;
	}    // namespace v1
}    // namespace gltfpp
