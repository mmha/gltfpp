#pragma once
#include "Error.h"
#include "detail/Byte.h"
#include <json.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		class Buffer {
			public:
			Buffer() = default;

			std::vector<byte> &operator*();
			const std::vector<byte> &operator*() const;
			std::vector<byte> *operator->();
			const std::vector<byte> *operator->() const;
			std::vector<byte> &get();
			const std::vector<byte> &get() const;

			option<std::string> uri;
			option<std::string> name;
			option<nlohmann::json> extensions;
			option<nlohmann::json> extras;
			std::vector<byte> data;
		};

		auto parse(Buffer &b);
	}	// namespace v1
}	// namespace gltfpp
