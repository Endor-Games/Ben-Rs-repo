#pragma once

#include <vector>

#include "Layer.h"

namespace Engine {
	class LayerStack
	{
	public:
		~LayerStack();

		// Push layer/overlay to the layers vector
		void PushLayer(Layer* pLayer);
		void PushOverlay(Layer* pOverlay);

		// Pop a layer/overlay from the layers vector
		void PopLayer(Layer* pLayer);
		void PopOverlay(Layer* pOverlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
		
		uint32_t m_layerIndex = 0;
	};
}
