#pragma once
#include "GL\glew.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"
#include "GLFW\glfw3.h"
#include <vector>
#include <string>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

