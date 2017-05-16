#pragma once
#include "../glTF.h"
#include "Buffer.h"
#include "BufferView.h"
#include "Parsing.h"
#include "URI.h"

namespace gltfpp {
	inline namespace v1 {
		inline gltf_result<void> from_json(const nlohmann::json &j, glTF &g) {
			ParseContext ctx{&g, &j};
			auto result = aggregate(g)(ctx);

			if(!result) {
				return result.error();
			}
			return {};
		}
	}
}
