#pragma once
#include "Accessor.h"
#include "Animation.h"
#include "Asset.h"
#include "Buffer.h"
#include "BufferView.h"
#include "Camera.h"
#include "Error.h"
#include "Image.h"
#include "Material.h"
#include "Mesh.h"
#include "Node.h"
#include "Sampler.h"
#include "Scene.h"
#include "Skin.h"
#include "Texture.h"
#include <boost/hana/define_struct.hpp>
#include <json.hpp>
#include <vector>

namespace gltfpp {
	inline namespace v1 {
		struct glTF {
			BOOST_HANA_DEFINE_STRUCT(glTF,
									 (Asset, asset),
									 (option<std::vector<Animation>>, animations),
									 (option<std::vector<Buffer>>, buffers),
									 //(option<std::vector<BufferView>>, bufferViews),
									 (option<nlohmann::json>, extensions),
									 (option<nlohmann::json>, extras));
			/*
			std::vector<Camera> cameras;
			std::vector<Image> images;
			std::vector<Material> materials;
			std::vector<Mesh> meshes;
			std::vector<Node> nodes;
			std::vector<Sampler> samplers;
			std::vector<Scene> scenes;
			std::vector<Skin> skins;
			std::vector<Texture> textures;
			Scene *scene;
			*/
		};

		gltf_result<void> from_json(const nlohmann::json &j, glTF &a);
	}	// namespace v1
}	// namespace gltfpp
