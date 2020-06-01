#pragma once

#include "Util/Log.h"
#include "Graphics//Window.h"
#include "Graphics/Layer/LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Graphics/Gui/GuiLayer.h"

namespace Engine {
	class Application
	{
	public:
		Application(const std::string& name = "Engine", uint32_t width = 1280, uint32_t height = 720);
		
		virtual ~Application() = default;

		// Run the application
		void Run();

		// Handle application events
		void OnEvent(Event& e);

		// Push a new layer to the layers vector
		void PushLayer(Layer* pLayer);

		// Push a new overlay to the overlays vector
		void PushOverlay(Layer* pLayer);

		// Get the window instance
		[[nodiscard]] Graphics::Window& GetWindow() const { return *m_pWindow; }

		// Get the application singleton instance
		static Application& Get() { return *s_pInstance; }

	private:
		// Handle application window closing
		bool OnWindowExit(WindowEvent_Close& e);

		// Scoped window instance
		std::unique_ptr<Graphics::Window> m_pWindow;

		// Single layer to handle Gui
		GuiLayer* m_pGuiLayer;

		// Boolean to check if the app is still running
		bool m_isRunning = true;

		// Vector to store all layers drawn on screen
		LayerStack m_layerStack;

		// Time since last frame
		float m_lastFrameTime = 0.0f;

		// Static application singleton instance
		static Application* s_pInstance;
	};
}
