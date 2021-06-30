#pragma once

#include <vector>
#include "byteCat/app/Layer.h"
#include "byteCat/Core.h"

namespace BC
{
	class BYTECAT_API LayerStack
	{
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;

	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	};
}
