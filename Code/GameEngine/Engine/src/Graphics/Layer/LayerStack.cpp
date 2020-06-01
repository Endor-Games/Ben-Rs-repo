#include "pch.h"
#include "LayerStack.h"

namespace Engine {
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* pLayer)
	{
		m_layers.emplace(m_layers.begin() + m_layerIndex, pLayer);
		m_layerIndex++;
		pLayer->OnLoad();
	}

	void LayerStack::PushOverlay(Layer* pOverlay)
	{
		m_layers.emplace_back(pOverlay);
		pOverlay->OnLoad();
	}

	void LayerStack::PopLayer(Layer* pLayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerIndex, pLayer);
		if (it != m_layers.begin() + m_layerIndex)
		{
			pLayer->OnExit();
			m_layers.erase(it);
			m_layerIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* pOverlay)
	{
		auto it = std::find(m_layers.begin() + m_layerIndex, m_layers.end(), pOverlay);
		if (it != m_layers.end())
		{
			pOverlay->OnExit();
			m_layers.erase(it);
		}
	}
}
