#pragma once

#include <vector>

namespace BC
{
	struct VAO
	{
		unsigned int id;
		unsigned int vertexCount;

		std::vector<unsigned int> vbos;
	};

	
	class Mesh
	{
	public:
		std::shared_ptr<VAO> vao;
		
		Mesh(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices);
		~Mesh();
		
		void bind() const;
		void unbind() const;
	};
}
