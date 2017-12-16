#pragma once
#ifndef COLOR
#define COLOR_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"

class Color
{

public:
	Color();

	void setStartingSequenceColor();
	void setCustomColor(GLfloat colorR, GLfloat colorG, GLfloat colorB, GLfloat numOfDrawingpoints);

	inline void setColorSize(int size) { this->m_colorSize = size; }
	inline void setColorData(GLfloat *colorData) { this->m_colorData = colorData; }

	inline int GetColorSize() { return m_colorSize; }
	inline GLfloat* GetColorData() { return m_colorData; }

	void fadingColor(GLfloat redColor, GLfloat greenColor, GLfloat blueColor) {
		for (int i = 0; i < 12 * 3; i++) {
			m_colorData[3 * i + 0] = redColor;
			m_colorData[3 * i + 1] = greenColor;
			m_colorData[3 * i + 2] = blueColor;
		}
	}


private:
	GLfloat *m_colorData;
	int m_colorSize;
};
#endif;
