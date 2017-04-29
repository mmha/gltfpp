#include "Buffer.h"

namespace gltfpp {
	inline namespace v1 {
		std::vector<byte> &Buffer::operator*() {
			return data;
		}

		const std::vector<byte> &Buffer::operator*() const {
			return data;
		}

		std::vector<byte> *Buffer::operator->() {
			return &data;
		}

		const std::vector<byte> *Buffer::operator->() const {
			return &data;
		}

		std::vector<byte> &Buffer::get() {
			return data;
		}

		const std::vector<byte> &Buffer::get() const {
			return data;
		}
	}	// namespace v1
}	// namespace gltfpp
