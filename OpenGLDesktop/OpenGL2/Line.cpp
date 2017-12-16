#include "C:\Users\Admin\Documents\Visual Studio 2017\Projects\OpenGLDesktop\OpenGLDesktop\OpenGL2\Line.h"

Line::Line() {
	static GLfloat lineBufferData[] = {
		(0.0f / (1000 - 0)) * (1 - (-1)) + (-1), (0.0f / (1000 - 0)) * (1 - (-1)) + (-1), (0.0f / (1000 - 0)) * (1 - (-1)) + (-1),
		(1000.0f / (1000 - 0)) * (1 - (-1)) + (-1), (1000.0f / (1000 - 0)) * (1 - (-1)) + (-1), (1000.0f / (1000 - 0)) * (1 - (-1)) + (-1)
	};
	printf("help");
	GLfloat *data = lineBufferData;
	this->m_lineData = data;
	this->m_lineSize = sizeof(lineBufferData);
}

void Line::setData()
{
}

