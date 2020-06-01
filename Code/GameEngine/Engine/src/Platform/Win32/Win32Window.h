#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Graphics/Window.h"
#include "Events/WindowEvent.h"

namespace Engine::Graphics {
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProps& props) { Init(props); };
		virtual ~Win32Window() { Release(); };

		void OnUpdate() override;

		// Event
		void SetEventCallback(const EventCallbackFn& callback) override { m_data.eventCallback = callback; }

		// Vsync
		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return m_data.vsync; };

		// Window
		virtual void* GetNativeWindow() const { return m_pWindow; }
		uint32_t GetWidth() const override { return m_data.width; }
		uint32_t GetHeight() const override { return m_data.height; }
		
	private:
		struct WindowData
		{
			std::string title;
			uint32_t width;
			uint32_t height;
			bool vsync;
			EventCallbackFn eventCallback;
		};
		
		virtual void Init(const WindowProps& props);
		virtual void Release();
		
		GLFWwindow* m_pWindow;
		WindowData m_data;
	};
}
