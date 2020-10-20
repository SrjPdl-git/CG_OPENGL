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
		Mesh()
			:vertexArrayObject(NULL),
			 vertexBufferObject(NULL),
			 indexBufferObject(NULL),
			 verticesCount(0),
			 indicesCount(0),
			 vertices(NULL),
			 indices(NULL)
		{}

		void create(float* vertices, uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount);
		void render();


};

