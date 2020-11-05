#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
class Light
{
	private:
		float ambientIntensity;
		float diffuseIntensity;
		glm::vec3 colour;
		glm::vec3 direction;

		uint32_t uLightColor;
		uint32_t uAmbientIntensity;
		uint32_t uDiffuseIntensity;
		uint32_t uDirection;

		uint32_t program;
	public:
		void update(glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f), float ambientIntensity = 1.f, float diffuseIntensity=1.f, glm::vec3 direction=glm::vec3(-1.f,-1.f,0.f));
		Light(uint32_t shaderProgram);
		~Light();
};

