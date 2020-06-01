#pragma once

#include "Camera.h"
#include "Events/WindowEvent.h"
#include "Util/Timestep.h"

namespace Engine::Graphics {
	class CameraController
	{
	public:
		CameraController(const float aspectRatio, const bool doRotation = false) :
			m_aspectRatio(aspectRatio),
			m_Camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio* m_zoomLevel, -m_zoomLevel, m_zoomLevel),
			m_doRotation(doRotation)
		{};

		// Update the camera
		void OnUpdate(Timestep timeStep);

		// TODO: Add system to handle camera controls
		// Handle application events
		void OnEvent(Event& e);

		// Get the camera instance
		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		// Get the camera's zoom level
		float GetZoomLevel() const { return m_zoomLevel; }
		void SetZoomLevel(float level) { m_zoomLevel = level; }

	private:
		// Handle scaling the camera when the window is resized
		bool OnWindowResized(WindowEvent_Resize& e);

		// Parameters
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		bool m_doRotation = false;
		float m_movementSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		// Camera instance
		Camera m_Camera;

		// Transforms
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};
}
