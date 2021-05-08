#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/Loader.h"

namespace BC
{
	namespace Loader
	{
		static unsigned int createVAO();
		static void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data);
		static void unbindVAO();

		static std::vector<GLuint> vaos;
		static std::vector<GLuint> vbos;

		RawModel LoadToVAO(std::vector<float>& positions)
		{
			const GLuint vaoID = createVAO();
			storeDataInAttributeList(0, 3, positions);
			unbindVAO();
			return { vaoID,  (unsigned int) (positions.size() / 3) };
		}

		void CleanUp()
		{
			glDeleteVertexArrays(static_cast<GLsizei>(vaos.size()), &vaos[0]);
			vaos.clear();
			glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
			vbos.clear();
		}

		static GLuint createVAO()
		{
			GLuint vaoID;
			// Create new VAO
			glGenVertexArrays(1, &vaoID);
			vaos.push_back(vaoID);
			// Bind the VAO
			glBindVertexArray(vaoID);
			return vaoID;
		}

		static void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
		{
			GLuint vboID;
			// Create new VBO
			glGenBuffers(1, &vboID);
			vbos.push_back(vboID);
			// Bind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			// Put data in the VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
			// Put the VBO in the VAO
			glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
			// Unbind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		static void unbindVAO()
		{
			glBindVertexArray(0);
		}
	}
}
