#pragma once

#include <Engine.h>
#include <Graphics.h>

using namespace Engine;
using namespace Engine::Graphics;

class CustomLayer : public Layer
{
public:
	CustomLayer() : m_cameraController(16.0f / 9.0f) {};
	virtual ~CustomLayer() = default;;

	virtual void OnLoad() override;
	virtual void OnEvent(Event& event) override;
	virtual void OnUpdate(const Timestep timeStep) override;
	virtual void OnGuiDraw() override;
	virtual void OnExit() override;
	
private:
	Shader* m_shader;
	CameraController m_cameraController;
	
	GLuint m_quadVA;
	GLuint m_quadVB;
	GLuint m_quadIB;

	glm::vec4 m_defaultColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_color = m_defaultColor;
};
