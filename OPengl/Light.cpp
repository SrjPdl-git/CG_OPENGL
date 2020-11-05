#include "Light.h"

void Light::update(glm::vec3 lightColor, float ambientIntensity, float diffuseIntensity, glm::vec3 direction)
{
	this->colour = lightColor;
	this->ambientIntensity = ambientIntensity;
	this->diffuseIntensity = diffuseIntensity;
	this->direction = direction;

	glUniform3fv(uLightColor,1, glm::value_ptr(this->colour));
	glUniform1f(uAmbientIntensity, this->ambientIntensity);
	glUniform1f(uDiffuseIntensity, this->diffuseIntensity);
	glUniform3fv(uDirection, 1, glm::value_ptr(this->direction));
}

Light::Light(uint32_t shaderProgram)
	:ambientIntensity(1.f),
	 diffuseIntensity(1.f),
	 colour(glm::vec3(1.f, 1.f, 1.f)),
	 direction(glm::vec3(0.f,-1.f,0.f)),
	 program(shaderProgram)
{
	uAmbientIntensity = glGetUniformLocation(program, "directionalLight.ambientStrength");
	uLightColor = glGetUniformLocation(program, "directionalLight.colour");
	uDirection = glGetUniformLocation(program, "directionalLight.direction");
	uDiffuseIntensity = glGetUniformLocation(program, "directionalLight.diffuseStrength");
}

Light::~Light()
{
}
