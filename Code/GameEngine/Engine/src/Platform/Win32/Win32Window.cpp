#include "pch.h"
#include "Win32Window.h"

namespace Engine::Graphics {	
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(const int error, const char* description)
	{
		LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new Win32Window(props);
	}

	void Win32Window::Init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		if (!s_GLFWInitialized)
		{
			const int success = glfwInit();
			ENGINE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_pWindow = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), m_data.title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_pWindow);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		ENGINE_ASSERT(status, "Failed to initialize Glad!");

		LOG_INFO("OpenGL Info:");
		LOG_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("Version: {0}", glGetString(GL_VERSION));

		glfwSetWindowUserPointer(m_pWindow, &m_data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* window, const int width, const int height){
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = height;

			WindowEvent_Resize event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* window){
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowEvent_Close event;
			data.eventCallback(event);
		});
	}

	void Win32Window::Release()
	{
		glfwDestroyWindow(m_pWindow);
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_pWindow);
	}

	void Win32Window::SetVSync(const bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = enabled;
	}
}
