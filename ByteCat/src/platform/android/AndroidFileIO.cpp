#ifdef BC_PLATFORM_ANDROID
#include "bcpch.h"
#include "byteCat/utils/FileIO.h"

namespace BC
{
	namespace Utils
	{		
		std::string FileIO::ReadFileIntoString(const std::string& path)
		{
			LOG_INFO("Going to read file: %s", path.c_str());

			FILE* file = fopen(path.c_str(), "w+");

			if (file != NULL)
			{
				fputs("HELLO WORLD!\n", file);
				fflush(file);
				fclose(file);
			}
			
			int c;
			FILE* fp = fopen(path.c_str(), "r");
			while (1) {
				c = fgetc(fp);
				if (feof(fp)) {
					break;
				}
				LOG_INFO("%c", c);
			}
			fclose(fp);
			
			return "";
			
			// std::ifstream inputStream(path, std::ios::in);
			//
			// if (!inputStream.is_open()) {
			// 	LOG_ERROR("Could not open file: %s, do you have READ_EXTERNAL_STORAGE permissions?", path.c_str());				
			// 	return "";
			// }
			//
			// std::string text = std::string((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
			//
			// inputStream.close();
			//
			// return text;
		}
	}
}
#endif


/*
 * Nog laten werken:
 * - Textures vanuit file inladen
 * - Shaders vanuit file inladen
 */