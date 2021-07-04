#pragma once

#include <vector>
#include "byteCat/app/Layer.h"

namespace BC
{
	/*
	 * Class LayerStack:
	 *		This class holds all the layers in the application and updates them every frame.
	 */
	class LayerStack
	{
	private:
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;

	public:
		LayerStack() = default;
		~LayerStack();

		// Add a new layer to the stack
		void pushLayer(Layer* layer);
		// Add an overlay to the stack (gets rendered on top of the layers)
		void pushOverlay(Layer* overlay);
		// Remove a layer from the stack
		void popLayer(Layer* layer);
		// Remove an overlay from the stack
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	};
}
