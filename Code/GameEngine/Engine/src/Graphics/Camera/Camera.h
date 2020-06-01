#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine::Graphics {
	class Camera
	{
	public:
		Camera(const float left, const float right, const float bottom, const float top);

		// Position
		[[nodiscard]] const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }

		// Rotation
		[[nodiscard]] float GetRotation() const { return m_rotation; }
		void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

		// Projection matrix
		[[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return m_projection; }
		void SetProjection(const float left, const float right, const float bottom, const float top);

		// View Matrix
		[[nodiscard]] const glm::mat4& GetViewMatrix() const { return m_view; }

		// View Projection Matrix
		[[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjection; }

	private:
		// Update the view matrix
		void RecalculateViewMatrix();

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;
	};
}
