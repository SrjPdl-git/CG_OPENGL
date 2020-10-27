#include "Light.h"

void Light::update(glm::vec3 lightColor, float ambientIntensity)
{
	this->lightColor = lightColor;
	this->ambientIntensity = ambientIntensity;
	glUniform3fv(uLightColor,1, glm::value_ptr(this->lightColor));
	glUniform1f(uAmbientIntensity, this->ambientIntensity);
}

Light::Light(uint32_t shaderProgram)
	:ambientIntensity(1.f),
	 lightColor(glm::vec3(1.f, 1.f, 1.f)),
	 program(shaderProgram)
{
	uAmbientIntensity = glGetUniformLocation(program, "directionalLight.ambientStrength");
	uLightColor = glGetUniformLocation(program, "directionalLight.lightColour");
}

Light::~Light()
{
}
