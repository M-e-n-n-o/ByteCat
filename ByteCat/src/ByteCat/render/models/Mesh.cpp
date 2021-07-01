#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/models/Mesh.h"
#include "byteCat/render/Loader.h"

namespace BC
{
	Mesh::Mesh(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices)
	{
		vao = std::make_shared<VAO>(Loader::LoadToVAO(positions, textureCoords, indices));
	}

	Mesh::~Mesh()
	{
		for (VBO& vbo : vao->vbos)
		{
			glDeleteBuffers(1, &vbo.id);
		}
		
		glDeleteVertexArrays(1, &vao->id);
	}

	void Mesh::bind() const
	{
		glBindVertexArray(vao->id);
	}

	void Mesh::unbind() const
	{
		glBindVertexArray(0);
	}

	std::vector<float>& Mesh::getVertexPositions() const
	{
		for (VBO& vbo : vao->vbos)
		{
			if (vbo.type == VboType::VertexPos)
			{
				return vbo.data;
			}
		}

		return std::vector<float>();
	}
}
