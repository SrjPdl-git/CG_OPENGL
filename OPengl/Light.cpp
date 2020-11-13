#include "Light.h"

void Light::update(glm::vec3 lightColor, float ambientReflectivity, float diffuseReflectivity, glm::vec3 direction)
{
	this->colour = lightColor;
	this->ambientReflectivity = ambientReflectivity;
	this->diffuseReflectivity = diffuseReflectivity;
	this->direction = direction;

	glUniform3fv(uColor,1, glm::value_ptr(this->colour));
	glUniform1f(uAmbientReflectivity, this->ambientReflectivity);
	glUniform1f(uDiffuseReflectivity, this->diffuseReflectivity);
	glUniform3fv(uDirection, 1, glm::value_ptr(this->direction));
}

Light::Light(uint32_t shaderProgram)
	:ambientReflectivity(1.f),
	 diffuseReflectivity(1.f),
	 colour(glm::vec3(1.f, 1.f, 1.f)),
	 direction(glm::vec3(0.f,-1.f,0.f)),
	 program(shaderProgram)
{
	uAmbientReflectivity = glGetUniformLocation(program, "directionalLight.ambientReflectivity");
	uColor = glGetUniformLocation(program, "directionalLight.colour");
	uDirection = glGetUniformLocation(program, "directionalLight.direction");
	uDiffuseReflectivity = glGetUniformLocation(program, "directionalLight.diffuseReflectivity");
}

Light::~Light()
{
}
