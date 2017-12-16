#pragma once
#ifndef INIT_WINDOW
#define INIT_WINDOW_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include <stdlib.h>
#include <string>

	class Init_Window
	{
	public:
		void CheckInitGLFW();
		void SetGLFWHints(unsigned short AA, unsigned short major_version, unsigned short minor_version, GLboolean forward_compatible);
		GLFWwindow* SetWindowProperties(float windowWidth, float windowHeight, std::string windowName, int monitor, int window);		
		
		inline float GetWindowWidth() { return m_windowHeight; }
		inline float GetWindowHeight() { return m_windowHeight;  }

	private:
		float m_windowHeight;
		float m_windowWidth;
	};
#endif;