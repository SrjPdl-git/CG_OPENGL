#include "Material.h"

Material::Material(uint32_t program)
	:specularReflectivity(NULL),
	 specularShine(2),
	 program(program)
{
	uSpecularReflectivity = glGetUniformLocation(program, "material.specularReflectivity");
	uSpecularShine = glGetUniformLocation(program, "material.specularShine");
}

void Material::update(float specularReflectivity, float specularShine)
{
	this->specularReflectivity = specularReflectivity;
	this->specularShine = specularShine;
	glUniform1f(uSpecularReflectivity, this->specularReflectivity);
	glUniform1f(uSpecularShine, this->specularShine);
}
