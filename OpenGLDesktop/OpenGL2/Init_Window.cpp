#include "Init_Window.h"
#include "LoadShaders.h"
#include "Triangle.h"


void Init_Window::CheckInitGLFW()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";
	}
}

void Init_Window::SetGLFWHints(unsigned short AA, unsigned short major_version, unsigned short minor_version, GLboolean forward_compatible)
{
	glfwWindowHint(GLFW_SAMPLES, AA);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, minor_version);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSwapInterval(1);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);   // Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);      // Antialias the lines
}

GLFWwindow* Init_Window::SetWindowProperties(float windowWidth, float windowHeight, std::string windowName, int GLFW_monitor, int GLFW_window)
{

	this->m_windowHeight = windowHeight;
	this->m_windowWidth = windowWidth;

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);

	if (window == NULL) {
		std::cout << "Error creating a window. Maybe the wrong OpenGL version?" << std::endl;
		glfwTerminate();

	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
	return window;

	}
