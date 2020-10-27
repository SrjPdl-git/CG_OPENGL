#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
class Light
{
	private:
		float ambientIntensity;
		glm::vec3 lightColor;
		uint32_t uLightColor;
		uint32_t uAmbientIntensity;
		uint32_t program;
	public:
		void update(glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f), float ambientIntensity = 1.f);
		Light(uint32_t shaderProgram);
		~Light();
};

