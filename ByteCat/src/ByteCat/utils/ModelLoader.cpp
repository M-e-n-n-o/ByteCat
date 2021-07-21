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
		
		static bool LoadObjModel(std::string filePath, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& normals, std::vector<float>& textureCoords)
		{
			filePath.insert(0, "res/");
			std::ifstream ifs(filePath);
			if (!ifs.is_open())
			{
				LOG_ERROR("Could not load the obj file: {0}", filePath);
				return false;
			}

			std::string line;

			try
			{
				while (true)
				{
					std::getline(ifs, line);
					std::vector<std::string> split_line = split(line, ' ');
					
					if (split_line.at(0) == "v")
					{
						vertices.push_back(std::stof(split_line.at(1)));
						vertices.push_back(std::stof(split_line.at(2)));
						vertices.push_back(std::stof(split_line.at(3)));
					} else if (split_line.at(0) == "vt")
					{
						textureCoords.push_back(std::stof(split_line.at(1)));
						textureCoords.push_back(std::stof(split_line.at(2)));
					} else if (split_line.at(0) == "vn")
					{
						normals.push_back(std::stof(split_line.at(1)));
						normals.push_back(std::stof(split_line.at(2)));
						normals.push_back(std::stof(split_line.at(3)));
					} else if (split_line.at(0) == "f")
					{
						break;
					}
				}

				while (line.at(0) == 'f')
				{
					std::vector<std::string> currentLine = split(line, ' ');
					
					std::vector<std::string> vertex1;
					split(currentLine.at(1), '/', vertex1);
					std::vector<std::string> vertex2;
					split(currentLine.at(2), '/', vertex2);
					std::vector<std::string> vertex3;
					split(currentLine.at(3), '/', vertex3);

					// Hier verder gaan
					
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
			return true;
		}


		
		// ----------------------------------------------------------------------
		// ------------------------- Generic Loader -----------------------------
		// ----------------------------------------------------------------------
		
		bool LoadModel(std::string filePath, std::vector<float>& vertices, std::vector<unsigned>& indices, std::vector<float>& normals, std::vector<float>& textureCoords)
		{
			if (filePath.find(".obj") != std::string::npos)
			{
				return LoadObjModel(filePath, vertices, indices, normals, textureCoords);
			}


			LOG_ERROR("Model type of \"{0}\" is not supported yet", filePath);
			return false;
		}
	}
}
