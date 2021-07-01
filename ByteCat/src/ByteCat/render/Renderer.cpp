#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/Renderer.h"


namespace BC
{
	void Renderer::prepare() const
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, 1.0f);
	}

	void Renderer::renderVAO(VAO& vao, Shader& shader) const
	{
		glBindVertexArray(vao.id);
		shader.bindTextures();
		glDrawElements(GL_TRIANGLES, vao.vertexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
