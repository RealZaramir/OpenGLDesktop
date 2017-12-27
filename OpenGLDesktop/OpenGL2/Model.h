#pragma once
#pragma once
#ifndef MODEL
#define MODEL_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"
#include <vector>
#include "C:\Users\Admin\Documents\Visual Studio 2017\Projects\OpenGLDesktop\OpenGLDesktop\GA\myVec3d.h"

class Model
{

public:
	Model();
	GLuint Init_Model(GLfloat* m_modelData);

	inline void setModelSize(int size) { this->m_modelSize = size; }
	inline void setModelData(GLfloat *modelData) { this->m_modelData = modelData; }

	inline int GetSize() { return m_modelSize; }
	GLfloat* GetData() { return m_modelData; }
	GLfloat* GetConvertedData() { return m_convertedModelData; }
	void convertMaxiData(std::vector <float>);

private:
	GLfloat *m_modelData;
	GLfloat* m_convertedModelData;
	int m_modelSize;
};
#endif;