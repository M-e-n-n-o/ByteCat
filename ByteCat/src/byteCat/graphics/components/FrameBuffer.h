#pragma once
#include <memory>
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Graphics
	{
		class FrameBuffer
		{
		public:
			virtual ~FrameBuffer() = default;

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual bool isComplete() const = 0;

			virtual void attachTexture(std::shared_ptr<Texture2D> texture) = 0;
			virtual void attachRenderBuffer(const TextureFormat& format) = 0;

			static std::shared_ptr<FrameBuffer> Create(const std::string& name, unsigned width, unsigned height);
		};
	}
}