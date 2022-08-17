#pragma once
#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
#include <string>
#include "byteCat/graphics/components/Shader.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLComputeShader : public Graphics::ComputeShader
		{
		private:
			std::string m_name;
			unsigned int m_programID;

		public:
			OpenGLComputeShader(const std::string& name, const std::string& computeSrc, bool isFilePath);
			~OpenGLComputeShader();

			void compute(unsigned numberOfGroupsX, unsigned numberOfGroupsY, unsigned numberOfGroupsZ) override;
			void waitToFinish() override;
			
			void setOutputTexture(std::shared_ptr<Graphics::Texture> texture, unsigned int textureUnit) override;
			
			const std::string& getName() const override { return m_name; }

		private:
			unsigned int loadShader(const std::string& shader, int type) const;
		};
	}
}
#endif