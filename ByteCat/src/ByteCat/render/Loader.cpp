#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/utils/stb_image.h"
#include "byteCat/render/Loader.h"

namespace BC
{
	namespace Loader
	{
		static unsigned int createVAO();
		static GLuint storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data);
		static GLuint bindIndicesBuffer(std::vector<int>& indices);


		VAO LoadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<int>& indices)
		{
			const GLuint vaoID = createVAO();
			
			std::vector<VBO> vbos;
			vbos.push_back({ bindIndicesBuffer(indices), VboType::Indices, std::vector<float>(indices.begin(), indices.end()) });
			vbos.push_back({ storeDataInAttributeList(0, 3, positions), VboType::VertexPos, positions });
			vbos.push_back({ storeDataInAttributeList(1, 2, textureCoords), VboType::TextureCoord, textureCoords });
			
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
			
			return { vaoID, (unsigned int)(indices.size()), vbos };
		}

		unsigned int Load2DTexture(std::string fileName, int& width, int& height)
		{
			int bpp;
			unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);

			GLuint textureID;
			glGenTextures(1, &textureID);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			stbi_image_free(imgData);
			return textureID;
		}

		static GLuint createVAO()
		{
			GLuint vaoID;
			// Create new VAO
			glGenVertexArrays(1, &vaoID);
			// Bind the VAO
			glBindVertexArray(vaoID);
			return vaoID;
		}

		static GLuint storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
		{
			GLuint vboID;
			// Create new VBO
			glGenBuffers(1, &vboID);
			// Bind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, vboID);
			// Put data in the VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), &data[0], GL_STATIC_DRAW);
			// Put the VBO in the VAO
			glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
			// Unbind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			return vboID;
		}

		static GLuint bindIndicesBuffer(std::vector<int>& indices)
		{
			GLuint vboID;
			// Create new VBO
			glGenBuffers(1, &vboID);
			// Bind the VBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
			// Put data in the VBO
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);
			return vboID;
		}
	}
}
