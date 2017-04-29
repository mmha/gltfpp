#pragma once
#include "../BufferView.h"
#include "../Error.h"
#include "../glTF.h"
#include "Parsing.h"

namespace gltfpp {
	inline namespace v1 {
		inline auto parse(BufferView &view) {
			return [&](ParseContext &ctx) -> gltf_result<ParseContext> {
				std::size_t bufferIdx{};
				std::ptrdiff_t offset{};
				std::ptrdiff_t length{};

				auto result = field(bufferIdx, "buffer")(ctx) >> field(offset, "byteOffset") >>
							  field(length, "byteLength") >> aggregate(view);

				if(!result) {
					return result;
				}

				if(!ctx.root->buffers || bufferIdx > ctx.root->buffers->size()) {
					return make_unexpected(gltf_error::index_out_of_range);
				}

				auto &buffer = ctx.root->buffers.value()[bufferIdx];

				view.buffer = std::addressof(buffer);
				view.span = {buffer.data.data() + offset, length};	// TODO range check

				return ctx;
			};
		}
	}	// namespace v1
}	// namespace gltfpp
