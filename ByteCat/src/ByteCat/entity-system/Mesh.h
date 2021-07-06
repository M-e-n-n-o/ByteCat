#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "byteCat/render/vertex-object/VertexArray.h"

namespace BC
{
	/*
	 * Class Mesh:
	 *		This class can be added to a GameObject to give it a 2D/3D object
	 */
	class Mesh: public ObjectComponent
	{
	private:
		std::shared_ptr<VertexArray> vao;
		
	public:
		Mesh();
		Mesh(float vertices[], unsigned int sizeV, unsigned int indices[], unsigned int sizeI);
		Mesh(float vertices[], unsigned int sizeV, unsigned int indices[], unsigned int sizeI, float textureCoords[], unsigned int sizeT);

		OBJ_COMP_TYPE;
		
		std::shared_ptr<VertexArray>& getVao() { return vao; }
	};
}
