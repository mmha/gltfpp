#pragma once
#include "../Accessor.h"
#include "../Error.h"
#include "../glTF.h"
#include "Parsing.h"

namespace gltfpp {
	inline namespace v1 {
		inline auto parse(Accessor &a) noexcept {
			return [&](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				std::size_t bufferViewIdx{};

				// clang-format off
				auto result =
				   aggregate(a)(ctx)
				>> field(bufferViewIdx, "bufferView");
				// clang-format on

				if(!result) {
					return result;
				}

				if(!ctx.root->bufferViews || bufferViewIdx > ctx.root->bufferViews->size()) {
					return make_unexpected(gltf_error::index_out_of_range);
				}

				auto &bufferView = ctx.root->bufferViews.value()[bufferViewIdx];

				a.bufferView = std::addressof(bufferView);

				return ctx;
			};
		}
	}    // namespace v1
}    // namespace gltfpp
