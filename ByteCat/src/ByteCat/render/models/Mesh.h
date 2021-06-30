#pragma once

#include <vector>

namespace BC
{
	enum class VboType
	{
		VertexPos,
		Indices,
		TextureCoord,
		Normal
	};

	struct VBO
	{
		unsigned int id;
		VboType type;

		std::vector<float>& data;
	};
	
	struct VAO
	{
		unsigned int id;
		unsigned int vertexCount;

		std::vector<VBO> vbos;
	};

	
	class Mesh
	{
	public:
		std::shared_ptr<VAO> vao;
		
		Mesh(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices);
		~Mesh();
		
		void bind() const;
		void unbind() const;

		std::vector<float>& getVertexPositions() const;
	};
}
