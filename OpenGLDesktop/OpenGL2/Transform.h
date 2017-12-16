#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
class Transform
{
public:
	
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) {
		this->m_pos = m_pos;
		this->m_rotation = m_rotation;
		this->m_scale = m_scale;
	}

	inline glm::mat4 GetModel() const {

		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 scaleMatrix = glm::scale(m_scale);
		glm::mat4 rotateXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotateYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotateZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));

		glm::mat4 rotationMatrix = rotateZMatrix * rotateYMatrix * rotateXMatrix;		//last matrix will be multiplide first: x*y then xy*z, order is important when multiplying matrices

		return posMatrix * rotationMatrix * scaleMatrix;
	}

	inline glm::vec3* GetPosition() { return &m_pos; }
	inline glm::vec3* GetRotation() { return &m_rotation; }
	inline glm::vec3* GetScale() { return &m_scale; }

	inline void SetPos(glm::vec3& pos) { this->m_pos = pos; }
	inline void SetRotation(glm::vec3& rotation) { this->m_rotation = rotation; }
	inline void SetScale(glm::vec3& scale) { this->m_scale = scale; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif;