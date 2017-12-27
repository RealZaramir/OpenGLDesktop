#pragma once
#ifndef CUBE
#define CUBE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"
static int i;
class Cube
{

public:
	Cube();

	void fadingProperties();
	void sendDatatoBuffer();

	inline void setCubeSize(int size) { this->m_cubeSize = size; }
	inline void setCubeData(GLfloat *cubeData) { this->m_cubeData = cubeData; }

	inline int GetSize() { return m_cubeSize; }
	inline GLfloat* GetData() { return m_cubeData; }
	inline GLuint GetCubeBufferInt() { return m_cubeBufferInt; }
private:
	GLfloat *m_cubeData;
	int m_cubeSize;
	int m_cubeBufferInt;
};
#endif;