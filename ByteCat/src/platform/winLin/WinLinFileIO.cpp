#ifdef BC_PLATFORM_PC
#include "bcpch.h"
#include "byteCat/utils/FileIO.h"

namespace BC
{
	namespace Utils
	{
		std::string FileIO::ReadFileIntoString(const std::string& path)
		{
			std::string newPath = path;
			newPath.insert(0, BC_ASSETS_FOLDER);
			std::ifstream inputStream(newPath, std::ios::in);

			if (!inputStream.is_open()) {
				LOG_ERROR("Could not open file: %s", newPath.c_str());
				return "";
			}

			std::string text = std::string((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());

			inputStream.close();

			return text;
		}
	}
}
#endif