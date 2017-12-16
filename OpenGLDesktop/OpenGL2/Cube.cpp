#include "Cube.h"

Cube::Cube()
{
	static  GLfloat g_vertex_buffer_data_cube[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	GLfloat *data = g_vertex_buffer_data_cube;
	this->m_cubeData = data;
	this->m_cubeSize = sizeof(g_vertex_buffer_data_cube);
	printf("");
}

void Cube::fadingProperties()
{
	if (i == 36) { exit; }
	i++;
	m_cubeData[3 * i + 0] = 0.8f;
	m_cubeData[3 * i + 1] = 1.0f;
	m_cubeData[3 * i + 2] = 0.9f;
}

void Cube::sendDatatoBuffer()
{
	GLuint bufferInt;
	glGenBuffers(1, &bufferInt);
	glBindBuffer(GL_ARRAY_BUFFER, bufferInt);
	glBufferData(GL_ARRAY_BUFFER, this->GetSize(), this->GetData(), GL_STATIC_DRAW);
	this->m_cubeBufferInt = bufferInt;
}
