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
				   aggregate(b)(ctx)
				>> field(byteLength, "byteLength");
				// clang-format on

				if(!result) {
					return result;
				}

				if(b.uri) {
					auto &uri = b.uri.get();
					b.data.reserve(byteLength);
					auto maybe_base64 = is_data_uri(uri);
					if(maybe_base64) {
						decode_embedded_base64(*maybe_base64, uri.end(), std::back_inserter(b.data));
					}
					else {
						// TODO load external resource if valid uri
						return make_unexpected(gltf_error::unimplemented);
					}
				}
				else {
					b.data.resize(byteLength);
				}

				return ctx;
			};
		}
	}	// namespace v1
}	// namespace gltfpp
