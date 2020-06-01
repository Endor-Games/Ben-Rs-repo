#pragma once

#include "pch.h"

namespace Engine {
	enum class EventType
	{
		None = 0,
		ApplicationDraw,
		ApplicationTick,
		ApplicationUpdate,
		WindowClose,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		WindowResize,
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = (1 << 0),
	};

	class Event
	{
	public:
		bool handled = false;

		[[nodiscard]] virtual EventType GetEventType() const = 0;
		[[nodiscard]] virtual const char* GetName() const = 0;
		[[nodiscard]] virtual int GetCategoryFlags() const = 0;
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(const EventCategory category) { return GetCategoryFlags() & category; };
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); };
}
