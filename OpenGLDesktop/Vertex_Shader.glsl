#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

uniform mat4 transformation;
uniform mat4 mvp;
out vec3 fragmentColor;

void main(){
	fragmentColor = vertexColor;
	gl_Position =  mvp * transformation *  vec4(vertexPosition_modelspace, 1);
	gl_PorintSize = 5.0;
}