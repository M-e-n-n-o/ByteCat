#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/Renderer.h"

namespace BC
{
	namespace Renderer
	{
		void Prepare()
		{
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
		}

		void Render(RawModel& model)
		{
			// Enable the VAO of the model
			glBindVertexArray(model.vaoID);
			// Enable the VBO who is at position 0 (the positions of the model)
			glEnableVertexAttribArray(0);
			
			// Render the positions (vertices) of the model
			glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);
			
			// Unbind/disable the VBO from position 0
			glDisableVertexAttribArray(0);
			// Unbind the VAO
			glBindVertexArray(0);
		}
	}
}