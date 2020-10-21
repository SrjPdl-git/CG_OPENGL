#pragma once

#include <iostream>
#include<GL/glew.h>
#include <glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <fstream>

#ifndef str
#define str string
#endif 


#include<string>
#include <sstream>
class Shader
{	
	private:
		uint32_t program;

		uint32_t uModel;
		uint32_t uProjection;
	protected:
		std::string load(const char* path,uint32_t shaderType);
		uint32_t compile(const char *path,uint32_t shaderType);
		void attachAndLink(uint32_t vShaderID, uint32_t fShaderID);
	public:
		void create(const char* vertexShaderPath, const char* fragmentShaderPath);
		void updateUniforms(glm::mat4 * modelMatrix,glm::mat4 *projectionMatrix);
		Shader();
		~Shader();


};

