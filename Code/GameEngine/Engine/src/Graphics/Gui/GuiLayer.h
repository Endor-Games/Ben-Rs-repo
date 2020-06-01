#pragma once

#include "Graphics/Layer/Layer.h"
#include "Events/ApplicationEvent.h"

namespace Engine {
	class GuiLayer : public Layer
	{
	public:
		GuiLayer();
		~GuiLayer() = default;

		virtual void OnLoad() override;
		virtual void OnExit() override;

		// Begin drawing the gui layer
		void Begin();

		// End drawing the gui layer
		void End();

	private:
		float m_time = 0.0f;
	};
}
