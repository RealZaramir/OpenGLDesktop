#include "StartingSequence.h"

StartingSequence::StartingSequence()
{
	/*  -1.0f,-1.0f,-1.0f,		//Green
		-1.0f, 1.0f, 1.0f,		//RED		URDREIECK
		-1.0f, 1.0f, -1.0f, */

	static GLfloat startingSequence_buffer_data[] = {		//Buffer of the letter g
//1. Try x		y	  z
	    -1.0f, 2.0f,-2.0f,		//Green
		-1.0f, 3.0f, 1.0f,		//RED		T1
		-1.0f, 3.0f, -2.0f,		//Blue
		
		-1.0f, 2.0f, 1.0f,
		-1.0f, 3.0f, 1.0f,		//T2
		-1.0f, 2.0f, -2.0f,
		
		-1.0f,-2.0f, 2.0f,
		-1.0f, 3.0f, 1.0f,		//T3
		-1.0f, -2.0f, 1.0f,
		
		-1.0f, -2.0f, 2.0f,
		-1.0f, 3.0f, 2.0f,		//T4
		-1.0f, 3.0f, 1.0f,
		
		-1.0f, -2.0f,  1.0f,
		-1.0f, -2.0f,  -2.0f,	//T5
		-1.0f, -1.0f,  -2.0f,
		
		-1.0f, -1.0f, 1.0f,		
		-1.0f, -1.0f, -2.0f,		//T6
		-1.0f, -2.0f, 1.0f,
		
		-1.0f, -1.0f, -1.0f,
		-1.0f, -2.0f, -2.0f,		//T7
		-1.0f,  0.5f,  -2.0f,
		
		-1.0f, 0.5f, -1.0f,
		-1.0f, -1.0f, -1.0f,		//T8
		-1.0f, 0.5f, -2.0f,
	};
	GLfloat *data = startingSequence_buffer_data;
	this->m_startingSequenceData = data;
	this->m_startingSequenceSize = sizeof(startingSequence_buffer_data);
}

void StartingSequence::StartStartingSequence(GLuint& TransformationID, GLuint& MatrixID, glm::mat4& MVPMatrix, GLuint& colorbuffer, Color** color, GLFWwindow* windowLive, glm::mat4& testtrans)
{
	glm::mat4 oldtrans = glm::mat4(0.0f);

	(*color)->setStartingSequenceColor();
	GLuint startingSequenceBuffer;
	glGenBuffers(1, &startingSequenceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, startingSequenceBuffer);
	glBufferData(GL_ARRAY_BUFFER, StartingSequence::GetStartingSequenceSize(), StartingSequence::GetStartingSequenceData(), GL_STATIC_DRAW);

	clock_t t = clock();
	do {
		//enablePolygonMode();
		if (oldtrans != testtrans) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			sendMatrixtoGPUUniform(TransformationID, testtrans);
			sendMatrixtoGPUUniform(MatrixID, MVPMatrix);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, startingSequenceBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
			glDisableVertexAttribArray(0);

			sendMatrixtoGPUUniform(TransformationID, testtrans);
			sendMatrixtoGPUUniform(MatrixID, MVPMatrix);
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			//color->fadingColor(Red, Green, Blue);
			glBufferData(GL_ARRAY_BUFFER, (*color)->GetColorSize(), (*color)->GetColorData(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDisableVertexAttribArray(0);

			glfwSwapBuffers(windowLive);
		}
		glfwPollEvents();
		t = clock() - t;
	} while (t < 1000);
}

