#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture()
	:data(NULL),
	 width(NULL),
	 height(NULL),
	 channels(NULL),
	 texture(NULL)
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::load(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	data=stbi_load(path, &width, &height, &channels,0);
	if (!data)
	{
		std::cout << "ERROR::FAILED_TO_OPEN:\"" << path << "\"" << std::endl;
		return;
	}

}



void Texture::create(const char* path)
{
	load(path);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0,GL_RGB,GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void Texture::Activate()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
}
