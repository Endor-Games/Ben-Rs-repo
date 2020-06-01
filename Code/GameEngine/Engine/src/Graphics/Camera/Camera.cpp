#include "pch.h"
#include "Camera.h"

namespace Engine::Graphics {
	Camera::Camera(const float left, const float right, const float bottom, const float top) :
		m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
		m_view(1.0f)
	{
		m_viewProjection = m_projection * m_view;
	}

	void Camera::SetProjection(const float left, const float right, const float bottom, const float top)
	{
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_viewProjection = m_projection * m_view;
	}

	void Camera::RecalculateViewMatrix()
	{
		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_view = glm::inverse(transform);
		m_viewProjection = m_projection * m_view;
	}
}
