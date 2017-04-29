#include "glTF.h"
#include "parsers/all.h"

namespace gltfpp {
	inline namespace v1 {
		gltf_result<void> from_json(const nlohmann::json &j, glTF &g) {
			ParseContext ctx{&g, &j};
			auto result = aggregate(g)(ctx);

			if(!result) {
				return result.error();
			}
			return {};
		}
	}	// namespace v1
}	// namespace gltfpp
