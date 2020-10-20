#pragma once

#include <iostream>
#include<GL/glew.h>
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
	protected:
		std::string load(const char* path,uint32_t shaderType);
		uint32_t compile(const char *path,uint32_t shaderType);
		void attachAndLink(uint32_t vShaderID, uint32_t fShaderID);
	public:
		uint32_t create(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader()
		{
			glDeleteProgram(program);
		}


};

