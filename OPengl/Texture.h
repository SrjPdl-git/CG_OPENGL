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

		void load(const char* path);
	public:
		Texture();
		~Texture();
		void create(const char* path);
		void Activate();

};

