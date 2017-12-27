#include "Draw.h"
#include "Cube.h"

void sendMatrixtoGPUUniform(GLuint matrixID, glm::mat4 matrix )
{
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &matrix[0][0]);
}

void enablePolygonMode() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void disablePolygonMode() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawConnections()
{
}
/*
template<class t>
void defineBuffer(t *object, GLuint bufferData)
{
	glGenBuffers(1, &bufferData);
	glBindBuffer(GL_ARRAY_BUFFER, bufferData);
	glBufferData(GL_ARRAY_BUFFER, t->GetSize(), t->GetData(), GL_STATIC_DRAW);
}
*/