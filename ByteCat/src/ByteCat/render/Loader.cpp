#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/stb_image.h"
#include "byteCat/render/Loader.h"

namespace BC
{
	namespace Loader
	{
		static unsigned int createVAO();
		static void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data);
		static void unbindVAO();
		static void bindIndicesBuffer(std::vector<int>& indices);

		static std::vector<GLuint> vaos;
		static std::vector<GLuint> vbos;
		static std::vector<GLuint> textures;

		RawModel LoadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices)
		{
			const GLuint vaoID = createVAO();
			bindIndicesBuffer(indices);
			storeDataInAttributeList(0, 3, positions);
			storeDataInAttributeList(1, 2, textureCoords);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			unbindVAO();
			return { vaoID,  (unsigned int) (indices.size()) };
		}

		unsigned int LoadTexture(std::string fileName)
		{
			int width, height, bpp;

			fileName.insert(0, "res/");
			unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);

			GLuint textureID;
			glGenTextures(1, &textureID);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(imgData);
			textures.push_back(textureID);
			return textureID;
		}

		void CleanUp()
		{
			if (!vaos.empty())
			{
				glDeleteVertexArrays(static_cast<GLsizei>(vaos.size()), &vaos[0]);
				vaos.clear();
			}

			if (!vbos.empty())
			{
				glDeleteBuffers(static_cast<GLsizei>(vbos.size()), &vbos[0]);
				vbos.clear();
			}

			if (!textures.empty())
			{
				glDeleteTextures(static_cast<GLsizei>(textures.size()), &textures[0]);
				textures.clear();
			}
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

		static void bindIndicesBuffer(std::vector<int>& indices)
		{
			GLuint vboID;
			// Create new VBO
			glGenBuffers(1, &vboID);
			vbos.push_back(vboID);
			// Bind the VBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
			// Put data in the VBO
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
		}


		static void unbindVAO()
		{
			glBindVertexArray(0);
		}
	}
}
