#pragma once

#include "Event.h"

namespace Engine {
	class ApplicationEvent_Draw : public Event
	{
	public:
		ApplicationEvent_Draw() {}

		EVENT_CLASS_TYPE(ApplicationDraw)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ApplicationEvent_Tick : public Event
	{
	public:
		ApplicationEvent_Tick() {}

		EVENT_CLASS_TYPE(ApplicationTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ApplicationEvent_Update : public Event
	{
	public:
		ApplicationEvent_Update() {}

		EVENT_CLASS_TYPE(ApplicationUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
