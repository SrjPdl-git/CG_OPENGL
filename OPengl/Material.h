#pragma once
#include<gl/glew.h>
#include <iostream>
class Material
{
	private:
		float specularReflectivity;
		float specularShine;
		uint32_t program;
		uint32_t uSpecularReflectivity;
		uint32_t uSpecularShine;
		
	public:
		Material(uint32_t program);
		void update(float specularReflectivity, float specularShine);


};


