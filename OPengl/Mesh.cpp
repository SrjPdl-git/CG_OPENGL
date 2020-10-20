#include "Mesh.h"

void Mesh::create(float* vertices,uint32_t verticesCount, uint32_t* indices, uint32_t indicesCount)
{
	this->vertices = vertices;
	this->verticesCount = verticesCount;
	this->indicesCount = indicesCount;
	this->indices = indices;

	/*Creating and Binding Vertex Array Object*/
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	/*Creating and Binding Vertex Buffer Object*/
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, this->verticesCount*sizeof(float), vertices, GL_STATIC_DRAW);

	/*Enable and Setup Vertex Attribute Pointer*/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	/*creating and binding Index Buffer Object*/
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount*sizeof(uint32_t), indices, GL_STATIC_DRAW );


	/*unbinding VAO,VBO, and IBO*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

void Mesh::render()
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glDrawElements(GL_TRIANGLES,indicesCount, GL_UNSIGNED_INT,0);
}
