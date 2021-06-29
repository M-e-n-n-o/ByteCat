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
		glDeleteVertexArrays(1, &vao->id);
		glDeleteBuffers(static_cast<GLsizei>(vao->vbos.size()), &vao->vbos[0]);
	}

	void Mesh::bind() const
	{
		glBindVertexArray(vao->id);
	}

	void Mesh::unbind() const
	{
		glBindVertexArray(0);
	}
}
