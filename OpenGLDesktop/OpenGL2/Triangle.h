#pragma once
#ifndef TRIANGLE
#define TRIANGLE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"

class Triangle
{

public:
       Triangle() {
		static GLfloat g_vertex_buffer_data[] = {
			1.0f, 0.0f, -1.0f,
			-1.0f, 1.0f, 0.0f,
			1.0f,  0.0f, 1.0f
		};
		GLfloat *data = g_vertex_buffer_data;
		this->m_triangleData = data;
		this->m_triangleSize = sizeof(g_vertex_buffer_data);

	}

	inline void setTriangleSize(int size) { this->m_triangleSize = size; }
	inline void setTriangleData(GLfloat *triangleData) { this->m_triangleData = triangleData; }

	inline int GetTriangleSize() { return m_triangleSize;}
	inline GLfloat* GetTriangleData() { return m_triangleData; }

private:
	GLfloat *m_triangleData;
	int m_triangleSize;
};
#endif;