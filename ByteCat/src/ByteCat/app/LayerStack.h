#pragma once

#include <vector>
#include "byteCat/app/Layer.h"
#include "byteCat/Core.h"

namespace BC
{
	class LayerStack
	{
	private:
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;

	public:
		LayerStack() = default;
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	};
}
