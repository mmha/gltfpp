#include <cstdio>
#include <glTF.h>

int main(int argc, char **argv) {
	gltfpp::glTF g;
	nlohmann::json j(argv[1]);
	from_json(j, g);
	printf("%s", g.asset.copyright->c_str());
}
