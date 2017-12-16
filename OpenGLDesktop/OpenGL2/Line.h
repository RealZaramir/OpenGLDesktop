#pragma once
#ifndef TRIANGLE
#define TRIANGLE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"

class Line
{

public:
	Line();

	inline void setLineSize(int size) { this->m_lineSize = size; }
	inline void setLineData(GLfloat *lineData) { this->m_lineData = lineData; }

	inline int GetLineSize() { return m_lineSize; }
	inline GLfloat* GetLineData() { return m_lineData; }

	void setData();
private:
	GLfloat *m_lineData;
	int m_lineSize;
};
#endif;