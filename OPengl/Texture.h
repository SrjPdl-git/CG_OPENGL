#pragma once
#include<iostream>
#include <GL/glew.h>
#include <stb_image.h>
class Texture
{
	private:
		unsigned char* data;
		int32_t width;
		int32_t height;
		int32_t channels;
		uint32_t texture;
		uint32_t uTextureUnit;
		uint32_t program;

		void load(const char* path);
	public:
		Texture();
		Texture(uint32_t shaderProgram);
		~Texture();
		void create(const char* path, uint32_t textureUnit=GL_TEXTURE0);
		void Activate(uint32_t textureSlot);

};

