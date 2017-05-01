#pragma once
#include "../Buffer.h"
#include "../Error.h"
#include "Parsing.h"

namespace gltfpp {
	inline namespace v1 {
		inline auto parse(Buffer &b) {
			return [&](const ParseContext &ctx) -> gltf_result<ParseContext> {
				std::size_t byteLength{};

				// clang-format off
				auto result =
				   field(b.uri, "uri")(ctx)
				>> field(b.name, "name")
				>> field(byteLength, "byteLength")
				>> field(b.extras, "extras")
				>> field(b.extensions, "extensions");
				// clang-format on

				if(!result) {
					return result;
				}

				b.data.resize(byteLength);

				// TODO deserialize or download actual data

				return ctx;
			};
		}
	}	// namespace v1
}	// namespace gltfpp
