#include "bcpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/utils/ModelLoader.h"

namespace BC
{
	namespace ModelLoader
	{	
		// ----------------------------------------------------------------------
		// --------------------------- OBJ Loader -------------------------------
		// ----------------------------------------------------------------------

		static void split(const std::string& s, char delim, std::vector<std::string>& elems)
		{
			std::stringstream ss;
			ss.str(s);
			std::string item;
			while (getline(ss, item, delim)) {
				elems.push_back(item);
			}
		}

		static std::vector<std::string> split(const std::string& s, char delim)
		{
			std::vector<std::string> elems;
			split(s, delim, elems);
			return elems;
		}

		static void processVertex(const std::vector<std::string>& vertexData,
			const std::vector<glm::vec3>& normals,
			const std::vector<glm::vec2>& textures,
			std::vector<unsigned int>& indices,
			std::vector<float>& textureArray,
			std::vector<float>& normalArray)
		{
			unsigned int currentVertexPointer = std::stoi(vertexData.at(0)) - 1;
			indices.push_back(currentVertexPointer);

			glm::vec2 currentTexture = textures.at(std::stoi(vertexData.at(1)) - 1);
			textureArray[(currentVertexPointer * 2) % textureArray.size()] = currentTexture.x;
			textureArray[(currentVertexPointer * 2 + 1) % textureArray.size()] = 1 - currentTexture.y;

			glm::vec3 currentNorm = normals.at(std::stoi(vertexData.at(2)) - 1);
			normalArray[currentVertexPointer * 3] = currentNorm.x;
			normalArray[currentVertexPointer * 3 + 1] = currentNorm.y;
			normalArray[currentVertexPointer * 3 + 2] = currentNorm.z;
		}
		
		static bool LoadObjModel(std::string filePath, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& normals, std::vector<float>& textureCoords)
		{
			std::ifstream ifs(filePath);
			if (!ifs.is_open())
			{
				LOG_ERROR("Could not load the obj file: {0}", filePath);
				return false;
			}

			std::vector<glm::vec3> verticesT;
			std::vector<glm::vec3> normalsT;
			std::vector<glm::vec2> texturesT;
			std::string line;

			try
			{
				while (true)
				{
					std::getline(ifs, line);
					std::vector<std::string> splitline = split(line, ' ');
					
					if (splitline.at(0) == "v")
					{
						glm::vec3 vertex;
						vertex.x = std::stof(splitline.at(1));
						vertex.y = std::stof(splitline.at(2));
						vertex.z = std::stof(splitline.at(3));
						verticesT.push_back(vertex);
					}
					else if (splitline.at(0) == "vt")
					{
						glm::vec2 texture;
						texture.x = std::stof(splitline.at(1));
						texture.y = std::stof(splitline.at(2));
						texturesT.push_back(texture);
					}
					else if (splitline.at(0) == "vn")
					{
						glm::vec3 normal;
						normal.x = std::stof(splitline.at(1));
						normal.y = std::stof(splitline.at(2));
						normal.z = std::stof(splitline.at(3));
						normalsT.push_back(normal);
					}
					else if (splitline.at(0) == "f")
					{
						normals = std::vector<float>(verticesT.size() * 3);
						textureCoords = std::vector<float>(texturesT.size() * 2);
						break;
					}
				}

				while (line.at(0) == 'f')
				{
					std::vector<std::string> splitline = split(line, ' ');
					std::vector<std::string> vertex1 = split(splitline.at(1), '/');
					std::vector<std::string> vertex2 = split(splitline.at(2), '/');
					std::vector<std::string> vertex3 = split(splitline.at(3), '/');
					
					processVertex(vertex1, normalsT, texturesT, indices, textureCoords, normals);
					processVertex(vertex2, normalsT, texturesT, indices, textureCoords, normals);
					processVertex(vertex3, normalsT, texturesT, indices, textureCoords, normals);
					
					if (!std::getline(ifs, line))
					{
						break;
					}
				}
			}
			catch (...)
			{
				ifs.close();
				LOG_ERROR("An error occured while loading the model: {0}", filePath);
				return false;
			}
			
			ifs.close();

			vertices = std::vector<float>(verticesT.size() * 3);
			int p = 0;
			for (auto& vertex : verticesT)
			{
				vertices[p++] = vertex.x;
				vertices[p++] = vertex.y;
				vertices[p++] = vertex.z;
			}
			
			
			return true;
		}


		
		// ----------------------------------------------------------------------
		// ------------------------- Generic Loader -----------------------------
		// ----------------------------------------------------------------------
		
		bool LoadModel(std::string const& filePath, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& normals, std::vector<float>& textureCoords)
		{
			LOG_INFO("Loading model: {0}", filePath);
			
			if (filePath.find(".obj") != std::string::npos)
			{
				return LoadObjModel(filePath, vertices, indices, normals, textureCoords);
			}


			LOG_ERROR("Model type of \"{0}\" is not supported yet", filePath);
			return false;
		}
	}
}
