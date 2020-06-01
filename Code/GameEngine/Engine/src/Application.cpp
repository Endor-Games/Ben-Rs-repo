#include "pch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Engine {
	Application* Application::s_pInstance = nullptr;

	Application::Application(const std::string& name, uint32_t width, uint32_t height)
	{
		if (!s_pInstance)
			Log::Init();

		// If an instance already exists, get it
		ENGINE_ASSERT(!s_pInstance, "Application instance already exists!");
		s_pInstance = this;

		// Create a new application window
		m_pWindow = std::unique_ptr<Graphics::Window>(Graphics::Window::Create({ name, width, height }));
		m_pWindow->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		// Create a new imgui Gui layer and push it
		m_pGuiLayer = new GuiLayer();
		PushOverlay(m_pGuiLayer);
	}

	void Application::PushLayer(Layer* pLayer)
	{
		m_layerStack.PushLayer(pLayer);
	}

	void Application::PushOverlay(Layer* pLayer)
	{
		m_layerStack.PushOverlay(pLayer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		// Handle window close events
		dispatcher.Dispatch<WindowEvent_Close>(ENGINE_BIND_EVENT_FN(Application::OnWindowExit));

		// Iterate though each layer in reverse and handle the events on each
		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			const float time = static_cast<float>(glfwGetTime());
			const Timestep timestep = time - m_lastFrameTime;
			m_lastFrameTime = time;

			// Update each layer
			for (Layer* pLayer : m_layerStack)
				pLayer->OnUpdate(timestep);

			// Draw the gui
			m_pGuiLayer->Begin();
			for (Layer* pLayer : m_layerStack)
				pLayer->OnGuiDraw();
			m_pGuiLayer->End();

			// Update the window
			m_pWindow->OnUpdate();
		}
	}

	bool Application::OnWindowExit(WindowEvent_Close& e)
	{
		m_isRunning = false;
		return true;
	}
}
