#include <gltfpp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	gltfpp::glTF g;
	std::string str(data, data + size);
	nlohmann::json j(str);
	from_json(j, g);
	return 0;
}
