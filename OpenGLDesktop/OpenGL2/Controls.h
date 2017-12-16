#pragma once
#ifndef TRIANGLE
#define TRIANGLE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "glm\glm.hpp"
#include "Draw.h"
class Controls
{

public:
	Controls() {
		this->Red = 0.0f;
		this->Blue = 0.0f;
		this->Green = 0.0f;
		this->xPos = 0.0f;
		this->yPos = 0.0f;
		this->zPos = 0.0f;
		this->xRot = 0.0f;
		this->yRot = 0.0f;
		this->zRot = 0.0f;
		
		}
	void CheckControls(GLFWwindow* windowLive) {		

		if (glfwGetKey(windowLive, GLFW_KEY_RIGHT) == GLFW_PRESS) this->yRot += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_UP) == GLFW_PRESS) this->xRot += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_LEFT) == GLFW_PRESS) this->yRot -= 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_DOWN) == GLFW_PRESS) this->xRot -= 0.001f;			//IDEA - USE TRANSFORM.H TO SET POS AND ROT

		if (glfwGetKey(windowLive, GLFW_KEY_D) == GLFW_PRESS) this->yPos -= 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_W) == GLFW_PRESS) this->xPos += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_A) == GLFW_PRESS) this->yPos += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_S) == GLFW_PRESS) this->xPos -= 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_Q) == GLFW_PRESS) this->zPos += 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_E) == GLFW_PRESS) this->zPos -= 0.001f;
		if (glfwGetKey(windowLive, GLFW_KEY_P) == GLFW_PRESS) {
			enablePolygonMode();
			pressedKeys[10] = 'P';
		}
		if (std::find(std::begin(pressedKeys), std::end(pressedKeys), 'P') && (glfwGetKey(windowLive, GLFW_KEY_P) == GLFW_PRESS)) {
			disablePolygonMode();
			pressedKeys[10] = ' ';
		}
		//printf("%c", pressedKeys[10]);
	//	printf("%f", yRot);
	}

	inline float GetxRot() { return this->xRot; }
	inline float GetyRot() { return this->yRot; }
	inline float GetzRot() { return this->zRot; }
	inline float GetxPos() { return this->xPos; }
	inline float GetyPos() { return this->yPos; }
	inline float GetzPos() { return this->zPos; }
	inline float GetGreen() { return this->Green; }
	inline float GetRed() { return this->Red; }
	inline float GetBlue() { return this->Blue; }

private:
	float Red;
	float Blue;
	float Green;
	float xPos;
	float yPos;
	float zPos;
	float xRot;
	float yRot;
	float zRot;
	char pressedKeys[255];
};
#endif;