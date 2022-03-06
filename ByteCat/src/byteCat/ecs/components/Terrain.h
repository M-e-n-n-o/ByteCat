#pragma once
#include "byteCat/Log.h"
#include "byteCat/ecs/components/Mesh.h"
#include "byteCat/graphics/components/Texture.h"
#include "glm/gtx/dual_quaternion.hpp"

namespace BC
{
	struct Terrain : Mesh
	{
		std::shared_ptr<Texture2D> heightMap;
		
        float size;
		float maxHeight;

	private:
        std::vector<std::vector<float>> heights;
	
	public:
		
		Terrain(std::shared_ptr<Texture2D>& heightMap, float size, float maxHeight)
		: heightMap(heightMap), size(size), maxHeight(maxHeight)
		{
			vao = VertexArray::Create();
			
			int vertexCount = heightMap->getHeight();

            heights.resize(vertexCount);
            for (auto& height : heights)
                height.resize(vertexCount);
			
			int count = vertexCount * vertexCount;

            float* vertices = new float[count * 3];
            float* normals = new float[count * 3];
            float* texCoords = new float[count * 2];
            unsigned int* indices = new unsigned int[6 * (vertexCount - 1) * (vertexCount - 1)];

            int vertexPointer = 0;
            for (int i = 0; i < vertexCount; ++i) 
            {
                for (int j = 0; j < vertexCount; ++j) 
                {
                    vertices[vertexPointer * 3] = (float)j / ((float)vertexCount - 1) * size;
                    auto height = getHeight(j, i);
                    heights[j][i] = height;
                    vertices[vertexPointer * 3 + 1] = height;
                    vertices[vertexPointer * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;
                    auto normal = calculateNormal(j, i);
                    normals[vertexPointer * 3] = normal.x;
                    normals[vertexPointer * 3 + 1] = normal.y;
                    normals[vertexPointer * 3 + 2] = normal.z;
                    texCoords[vertexPointer * 2] = (float)j / ((float)vertexCount - 1);
                    texCoords[vertexPointer * 2 + 1] = (float)i / ((float)vertexCount - 1);
                    vertexPointer++;
                }
            }

            int pointer = 0;
            for (int gz = 0; gz < vertexCount - 1; gz++) 
            {
                for (int gx = 0; gx < vertexCount - 1; gx++) 
                {
                    unsigned int topLeft = (gz * vertexCount) + gx;
                    unsigned int topRight = topLeft + 1;
                    unsigned int bottomLeft = ((gz + 1) * vertexCount) + gx;
                    unsigned int bottomRight = bottomLeft + 1;
                    indices[pointer++] = topLeft;
                    indices[pointer++] = bottomLeft;
                    indices[pointer++] = topRight;
                    indices[pointer++] = topRight;
                    indices[pointer++] = bottomLeft;
                    indices[pointer++] = bottomRight;
                }
            }

            auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices));
            vao->setIndexBuffer(indexBuffer);

            auto verticesBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
            verticesBuffer->setLayout({ {ShaderDataType::Float3, "vertex"} });
            vao->addVertexBuffer(verticesBuffer);

            auto texCoordsBuffer = VertexBuffer::Create(texCoords, sizeof(texCoords));
            texCoordsBuffer->setLayout({ {ShaderDataType::Float2, "uv"} });
            vao->addVertexBuffer(texCoordsBuffer);

            auto normalsBuffer = VertexBuffer::Create(normals, sizeof(normals));
            normalsBuffer->setLayout({ {ShaderDataType::Float3, "normal"} });
            vao->addVertexBuffer(normalsBuffer);
			
            delete[] vertices;
            delete[] texCoords;
            delete[] normals;
            delete[] indices;
		}

	private:
		float getHeight(int x, int y)
		{
            return 0;
			
			if (x < 0 || x >= heightMap->getWidth() || y < 0 || y >= heightMap->getHeight())
			{
				return 0;
			}

			char pixel = heightMap->getValue(0, x, y);
			
			float normalized = pixel / 255;
			normalized = normalized * 2 - 1;
			normalized *= maxHeight;
			return normalized;
		}

        glm::vec3 Terrain::calculateNormal(int x, int z)
		{
            float heightL = getHeight(x - 1, z);
            float heightR = getHeight(x + 1, z);
            float heightD = getHeight(x, z - 1);
            float heightU = getHeight(x, z + 1);
			
            glm::vec3 normal = 
            {
                    heightL - heightR,
                    2.f,
                    heightD - heightU
            };

            normal = glm::normalize(normal);
            return normal;
        }
	};
}
