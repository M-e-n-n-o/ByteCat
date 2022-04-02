#include "bcpch.h"
#include "byteCat/app/LayerStack.h"

namespace BC
{
	LayerStack::~LayerStack()
	{		
		for (Layer* layer : m_layers)
		{
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		LOG_INFO("Adding a new layer to the application: {0}", layer->getName());

		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
		layer->onAttach();
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		LOG_INFO("Adding a new overlay to the application: {0}", overlay->getName());

		m_layers.emplace_back(overlay);
		overlay->onAttach();
	}

	// void LayerStack::popLayer(Layer* layer)
	// {
	// 	auto it = std::find(layers.begin(), layers.end(), layer);
	// 	if (it != layers.end())
	// 	{
	// 		layer->onDetach();
	// 		layers.erase(it);
	// 		layerInsertIndex--;
	// 	}
	// }
	//
	// void LayerStack::popOverlay(Layer* overlay)
	// {
	// 	auto it = std::find(layers.begin(), layers.end(), overlay);
	// 	if (it != layers.end())
	// 	{
	// 		overlay->onDetach();
	// 		layers.erase(it);
	// 	}
	// }
}
