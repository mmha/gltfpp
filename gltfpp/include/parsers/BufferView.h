#pragma once
#include "../BufferView.h"
#include "../Error.h"
#include "../glTF.h"
#include "Parsing.h"

namespace gltfpp {
	inline namespace v1 {
		inline auto parse(BufferView &view) noexcept {
			return [&](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				std::size_t bufferIdx{};
				std::ptrdiff_t offset{};
				std::ptrdiff_t length{};

				// clang-format off
				auto result =
				   field(bufferIdx, "buffer")(ctx)
				>> field(offset, "byteOffset")
				>> field(length, "byteLength")
				>> aggregate(view);
				// clang-format on

				if(!result) {
					return result;
				}

				if(!ctx.root->buffers || bufferIdx > ctx.root->buffers->size()) {
					return make_unexpected(gltf_error::index_out_of_range);
				}

				auto &buffer = ctx.root->buffers.value()[bufferIdx];

				if(length < 0 || static_cast<std::size_t>(offset) > buffer.uri->size() ||
				   static_cast<std::size_t>(offset + length) > buffer.uri->size()) {
					return make_unexpected(gltf_error::index_out_of_range);
				}

				view.buffer = std::addressof(buffer);
				view.span = {buffer.uri->data() + offset, length};

				return ctx;
			};
		}
	}    // namespace v1
}    // namespace gltfpp
