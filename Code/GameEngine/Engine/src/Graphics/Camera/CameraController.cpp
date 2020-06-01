#include "pch.h"
#include "CameraController.h"

namespace Engine::Graphics {
	void CameraController::OnUpdate(const Timestep)
	{
		if (m_doRotation)
		{
			if (m_rotation > 180.0f)
				m_rotation -= 360.0f;
			else if (m_rotation <= -180.0f)
				m_rotation += 360.0f;
		}

		m_Camera.SetPosition(m_position);
		m_Camera.SetRotation(m_rotation);

		m_movementSpeed = m_zoomLevel;
	}

	void CameraController::OnEvent(Event& e) {}

	bool CameraController::OnWindowResized(WindowEvent_Resize& e)
	{
		m_aspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}
}
