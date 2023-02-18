#ifdef BC_PLATFORM_ANDROID
#include "bcpch.h"
#include "byteCat/utils/FileIO.h"

#include <glfm.h>
#include <android/asset_manager.h>
#define FILE_COMPAT_ANDROID_ACTIVITY glfmAndroidGetActivity()
#include "../vendor/glfm/example/src/file_compat.h"

namespace BC
{
	namespace Utils
	{		
		std::string FileIO::GetRelativePath(const std::string& path)
		{
			char fullPath[PATH_MAX];
			fc_resdir(fullPath, sizeof(fullPath));
			strncat(fullPath, path.c_str(), sizeof(fullPath) - strlen(fullPath) - 1);

			return std::string(fullPath);
		}

		std::string FileIO::ReadFileIntoString(const std::string& path)
		{
			std::string relativePath = FileIO::GetRelativePath(path);
			char fullPath[PATH_MAX];
			strcpy(fullPath, relativePath.c_str());
			
			char* fileContent = NULL;
			FILE* file = fopen(fullPath, "rb");
			if (file) 
			{
				fseek(file, 0, SEEK_END);
				long length = ftell(file);
				fseek(file, 0, SEEK_SET);

				fileContent = (char*) malloc(length + 1);
				if (fileContent) 
				{
					fread(fileContent, length, 1, file);
					fileContent[length] = 0;
				}
				
				fclose(file);
			}
			
			if (!fileContent) 
			{
				LOG_ERROR("Couldn't read file: %s, do you have READ_EXTERNAL_STORAGE permissions?", fullPath);
				free(fileContent);
				return "";
			}

			std::string finalString(fileContent);
			free(fileContent);

			return finalString;
		}

		bool FileIO::GetDataFromAssets(const std::string& path, std::vector<unsigned char>& buffer)
		{
			std::string relativePath = FileIO::GetRelativePath(path);

			AAsset* asset = AAssetManager_open(FILE_COMPAT_ANDROID_ACTIVITY->assetManager, path.c_str(), AASSET_MODE_BUFFER);
			size_t fileLength = AAsset_getLength(asset);

			buffer.resize(fileLength);
			int64_t readSize = AAsset_read(asset, buffer.data(), buffer.size());

			AAsset_close(asset);

			return (readSize == buffer.size());
		}
	}
}
#endif