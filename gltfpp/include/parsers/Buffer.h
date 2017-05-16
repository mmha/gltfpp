#pragma once
#include "../Buffer.h"
#include "../Error.h"
#include "Parsing.h"
#include "URI.h"

namespace gltfpp {
	inline namespace v1 {
		inline auto parse(Buffer &b) {
			return [&](const ParseContext &ctx) -> gltf_result<ParseContext> {
				std::size_t byteLength{};

				// clang-format off
				auto result =
				   aggregate(b)(ctx)
				>> field(byteLength, "byteLength");
				// clang-format on

				if(!result) {
					return result;
				}

				if(!b.uri) {
					b.uri.emplace();
					b.uri->resize(byteLength);
				}

				return ctx;
			};
		}
	}	// namespace v1
}	// namespace gltfpp
