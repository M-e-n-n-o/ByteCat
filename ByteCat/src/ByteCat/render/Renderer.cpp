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

		void Render(TexturedModel& texturedModel)
		{
			RawModel model = texturedModel.rawModel;
			
			// Enable the VAO of the model
			glBindVertexArray(model.vaoID);
			// Enable the VBO who is at position 0 (the positions of the model)
			glEnableVertexAttribArray(0);
			// Enable the VBO who is at position 1 (the textureCoords of the model)
			glEnableVertexAttribArray(1);

			// Activate texture 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturedModel.texture.textureID);
			
			// Render the vertices of the model
			glDrawElements(GL_TRIANGLES, model.vertexCount, GL_UNSIGNED_INT, 0);
			
			// Unbind/disable the VBO from position 0
			glDisableVertexAttribArray(0);
			// Unbind/disable the VBO from position 1
			glDisableVertexAttribArray(1);
			// Unbind the VAO
			glBindVertexArray(0);
		}
	}
}