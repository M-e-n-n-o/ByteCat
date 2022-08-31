#ifdef BC_PLATFORM_ANDROID
#include "bcpch.h"
#include "byteCat/utils/FileIO.h"

#include <glfm.h>
#include <android/asset_manager.h>
#include <android/imagedecoder.h>
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

		void* GetImageFromAssets(const std::string& path)
		{
			std::string relativePath = FileIO::GetRelativePath(path);

			AAsset* asset = AAssetManager_open(FILE_COMPAT_ANDROID_ACTIVITY->assetManager, relativePath.c_str(), AASSET_MODE_STREAMING);
			AImageDecoder* decoder;

			int result = AImageDecoder_createFromAAsset(asset, &decoder);
			if (result != ANDROID_IMAGE_DECODER_SUCCESS)
			{
				LOG_ERROR("Couldn't decode asset: %s", relativePath.c_str());
				return nullptr;
			}

			const AImageDecoderHeaderInfo* info = AImageDecoder_getHeaderInfo(decoder);
			int width = AImageDecoderHeaderInfo_getWidth(info);
			int height = AImageDecoderHeaderInfo_getHeight(info);
			AndroidBitmapFormat format = (AndroidBitmapFormat)AImageDecoderHeaderInfo_getAndroidBitmapFormat(info);
			int stride = AImageDecoder_getMinimumStride(decoder);

			int size = height * stride;
			void* pixels = malloc(size);

			result = AImageDecoder_decodeImage(decoder, pixels, stride, size);
			if (result != ANDROID_IMAGE_DECODER_SUCCESS) 
			{
				LOG_ERROR("Couldn't decode asset: %s", relativePath.c_str());
				return nullptr;
			}

			AImageDecoder_delete(decoder);
			AAsset_close(asset);

			return pixels;
		}
	}
}
#endif

/* Te doen:
*	- Images inlezen werkt nog niet
*	- Structuur van FileIO en alles wat hiermee interact voelt rommelig
*/