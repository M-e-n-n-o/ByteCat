#include "bcpch.h"
#include "byteCat/utils/FileIO.h"

namespace BC
{
	namespace Utils
	{
		std::string FileIO::ReadFileIntoString(const std::string& path)
		{
			std::ifstream input_file(path);

			if (!input_file.is_open()) {
				LOG_ERROR("Could not open the file: {0}", path);
				return "";
			}

			std::string text = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

			input_file.close();

			return text;
		}
	}
}
