#pragma once
#pragma once
#ifndef MVP_H
#define MVP_H
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"

class MVP
{
public:
	inline glm::mat4 CreateMVPMatrix(float FOVDegree, float windowWidth, float windowHeight) {
		this->m_windowHeight = windowHeight;
		this->m_windowWidth = windowWidth;
		this->m_FOVDegree = FOVDegree;
		this->lookAt0 = glm::vec3(10.0f, 0.0f, 0.0f);
		this->lookAt1 = glm::vec3(0.0f, 0.0f, 0.0f);		//Position
		this->lookAt2 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FOVDegree), m_windowWidth / m_windowHeight, 0.1f, 100.0f); 
		this->ProjectionMatrix = ProjectionMatrix;
		glm::mat4 ViewMatrix = glm::lookAt(lookAt0, lookAt1, lookAt2);
		this->ViewMatrix = ViewMatrix;
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		this->ModelMatrix = ModelMatrix;
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		this->mvp = MVP;
		return MVP;
	}

	inline float GetfovDegree() { return m_FOVDegree; }
	inline glm::vec3* GetWindowHeight() { return &m_pos; }
	inline glm::vec3* GetRotation() { return &m_rotation; }
	inline glm::vec3* GetScale() { return &m_scale; }
	inline glm::mat4* GetProjectionMatrix() { return &ProjectionMatrix; }
	inline glm::mat4* GetViewMatrix() { return &ViewMatrix; }
	inline glm::mat4* GetModelMatrix() { return &ModelMatrix; }
	inline glm::mat4* GetMVP() { return &mvp; }

	inline void SetFOVDegree(float FOVDegree) { this->m_FOVDegree = FOVDegree; }
	inline void SetWindowHeight(float height) { this->m_windowHeight = height; }
	inline void SetWindowWidth(float width) { this->m_windowWidth = width; }
	inline void SetScale(glm::vec3& scale) { this->m_scale = scale; }
	inline void SetLocation(glm::vec3 position) { this->m_pos = position; }
	inline void SetProjectionMatrix(glm::mat4 projectionmatrix) { this->ProjectionMatrix = projectionmatrix; }
	inline void SetViewMatrix(glm::mat4 viewmatrix) { this->ViewMatrix = viewmatrix; }
	inline void SetModelMatrix(glm::mat4 modelmatrix) { this->ModelMatrix = modelmatrix; }
	inline void SetMVP(glm::mat4 given_mvp) { this->mvp = given_mvp; }

	inline glm::mat4 recalculateMatrix() { return this->mvp = this->ProjectionMatrix * this->ViewMatrix * this->ModelMatrix; }

	inline glm::mat4 calculateMVP() { return ProjectionMatrix * ViewMatrix * ModelMatrix; }
private:
	float m_FOVDegree;
	float m_windowHeight;
	float m_windowWidth;
	glm::vec3 m_pos;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::vec3 lookAt0;
	glm::vec3 lookAt1;
	glm::vec3 lookAt2;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 mvp;
};

#endif;