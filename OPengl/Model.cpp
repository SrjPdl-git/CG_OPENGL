#include "Model.h"


void Model::load(const char* filePath, uint32_t program)
{
	this->program = program;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
											 aiProcess_Triangulate			 
											|aiProcess_JoinIdenticalVertices
											);
	
	if (!scene)
	{
		std::cout<<"ERROR::FAILED_TO_LOAD:\"" << filePath << "\" : "<<importer.GetErrorString() << std::endl;
		return;
	}
	handleNode(scene->mRootNode, scene);

	handleTexture(scene);
}

void Model::render(glm::mat4* modelMatrix)
{
	for (uint32_t i = 0; i < meshes.size(); i++)
	{
		textures[textureIndex[i]]->Activate(GL_TEXTURE0);
		meshes[i]->update(modelMatrix);
		meshes[i]->render();
	}
}

void Model::handleNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		handleMesh(mesh, scene);
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		handleNode(node->mChildren[i], scene);
	}

}

void Model::handleMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector <float> vertices;
	std::vector <uint32_t> indices;
	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		//Vertex Position
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		//vertices.push_back(mesh->mNormals[i].x);
		//vertices.push_back(mesh->mNormals[i].y);
		//vertices.push_back(mesh->mNormals[i].z);

		if (mesh->HasNormals())
		{
			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);
		}
		else
		{
			vertices.insert(vertices.end(), { 0.f, 0.f, 0.f });
		}
		

		if (mesh->mTextureCoords[0])
		{
			vertices.push_back(mesh->mTextureCoords[0][i].x);
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}

	}

	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		/*aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);

		}
		*/

		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
		
	}

	if (!mesh->HasNormals())
	{
		Helper::calculateVertexNormal(&vertices[0], vertices.size(), &indices[0], indices.size(), 8, 3);
	}

	Mesh* nMesh = new Mesh;
	nMesh->create(&vertices[0], vertices.size(), &indices[0], indices.size(), this->program);
	meshes.push_back(nMesh);

	textureIndex.push_back(mesh->mMaterialIndex);

}

void Model::handleTexture(const aiScene* scene)
{
	textures.resize(scene->mNumMaterials);

	for (uint32_t i = 0; i < scene->mNumMaterials; i++)
	{
		textures[i] = nullptr;

		aiMaterial* material= scene->mMaterials[i];

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString filePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath);

			std::string relativePath = std::string("textures/") +
									   std::string(filePath.data).substr(std::string(filePath.data).rfind("\\")+1);

			textures[i] = new Texture(this->program, relativePath.c_str());
			//textures[i] = nTexture;
		}
		
		if(!textures[i])
		{
			textures[i] = new Texture(this->program, "textures/index.png");
			//textures[i] = nTexture;
		}
	}
}
