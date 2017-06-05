#pragma once
#include "../glTF.h"
#include "Accessor.h"
#include "Buffer.h"
#include "BufferView.h"
#include "Parsing.h"
#include "URI.h"

namespace gltfpp {
	inline namespace v1 {
		inline gltf_result<void> from_json(nlohmann::json const &j, glTF &g) noexcept {
			ParseContext ctx{&g, &j};
			auto result = aggregate(g)(ctx);

			if(!result) {
				return result.error();
			}
			return {};
		}
	}    // namespace v1
}    // namespace gltfpp
