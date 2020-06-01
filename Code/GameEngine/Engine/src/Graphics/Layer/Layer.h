#pragma once

#include "../../Events/Event.h"
#include "../../Util/Timestep.h"

namespace Engine {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_debugName(name) {};
		
		virtual ~Layer() = default;

		virtual void OnLoad() {}
		virtual void OnUpdate(const Timestep) {}
		virtual void OnGuiDraw() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnExit() {}

		[[nodiscard]] const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}
