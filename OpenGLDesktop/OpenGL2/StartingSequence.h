#pragma once
#ifndef STARTINGSEQUENCE
#define STARTINGSEQUENCE_H
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"
#include "Transform.h"
#include "Color.h"
#include "Init_Window.h"
#include <time.h>
#include "Draw.h"
class StartingSequence
{

public:
	StartingSequence();
	void StartStartingSequence(GLuint& TransformationID, GLuint& MatrixID, glm::mat4& MVPMatrix, GLuint& colorbuffer, Color** color, GLFWwindow* windowLive, glm::mat4& testtrans);
	inline void setStartingSequenceSize(int size) { this->m_startingSequenceSize = size; }
	inline void setStartingsequenceData(GLfloat *StartingSequenceData) { this->m_startingSequenceData = StartingSequenceData; }
	
	inline int GetStartingSequenceSize() { return m_startingSequenceSize; }
	inline GLfloat* GetStartingSequenceData() { return m_startingSequenceData; }

private:
	GLfloat *m_startingSequenceData;
	int m_startingSequenceSize;
};
#endif;#pragma once
