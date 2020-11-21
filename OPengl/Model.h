#pragma once

#ifndef str
#define str string
#endif 

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

#include "Helper.h"
#include "Mesh.h"
#include "Texture.h"
class Model
{
	private:
		uint32_t program;
		std::vector<Mesh*> meshes;
		std::vector<Texture*> textures;
		std::vector<uint32_t> textureIndex;

		void handleNode(aiNode* node, const aiScene* scene);
		void handleMesh(aiMesh* mesh, const aiScene* scene);
		void handleTexture(const aiScene* scene);
	public:
		void load(const char* filePath, uint32_t program);
		void render(glm::mat4* modelMatrix);


};

