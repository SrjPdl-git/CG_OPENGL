#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
class Light
{
	private:
		float ambientReflectivity;
		float diffuseReflectivity;
		glm::vec3 colour;
		glm::vec3 direction;

		uint32_t uColor;
		uint32_t uAmbientReflectivity;
		uint32_t uDiffuseReflectivity;
		uint32_t uDirection;

		uint32_t program;
	public:
		void update(glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f), float ambientReflectivity = 1.f, float diffuseReflectivity=1.f, glm::vec3 direction=glm::vec3(-1.f,-1.f,0.f));
		Light(uint32_t shaderProgram);
		~Light();
};

