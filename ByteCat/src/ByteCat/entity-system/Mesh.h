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
		Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);
		Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& textureCoords);
		
		std::shared_ptr<VertexArray>& getVao() { return vao; }
	};
}
