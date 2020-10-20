#pragma once
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>


class Mesh
{
	private:
		uint32_t vertexArrayObject;
		uint32_t vertexBufferObject;
		uint32_t indexBufferObject;
		uint32_t verticesCount;
		uint32_t indicesCount;
		float* vertices;
		uint32_t* indices;

	public:
		Mesh();

		void create(float* vertices, uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount);
		void render();


};

