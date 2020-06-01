#pragma once

#include "Event.h"

namespace Engine {
	class WindowEvent_Resize : public Event
	{
	public:
		WindowEvent_Resize(const uint32_t width, const uint32_t height)
			: m_width(width), m_height(height) {}

		[[nodiscard]] uint32_t GetWidth() const { return m_width; }
		[[nodiscard]] uint32_t GetHeight() const { return m_height; }

		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowEvent - Resize: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32_t m_width;
		uint32_t m_height;
	};

	class WindowEvent_Close : public Event
	{
	public:
		WindowEvent_Close() {}

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
