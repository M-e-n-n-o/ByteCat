#pragma once

namespace BC
{
	namespace Utils
	{
		class FileIO
		{
		public:
			static std::string GetRelativePath(const std::string& path);

			static std::string ReadFileIntoString(const std::string& path);
			
#ifdef BC_PLATFORM_ANDROID
			// Note: Manually delete the data!
			static bool GetDataFromAssets(const std::string& path, std::vector<unsigned char>& buffer);
#endif
		};
	}
}
