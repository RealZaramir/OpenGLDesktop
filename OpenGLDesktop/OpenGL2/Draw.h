#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "glm\glm.hpp"
#include "Cube.h"

void sendMatrixtoGPUUniform(GLuint matrixID, glm::mat4 matrix);
void enablePolygonMode();
void disablePolygonMode();

void drawConnections();
//template <typename t> void defineBuffer(t* object, GLuint bufferData);
