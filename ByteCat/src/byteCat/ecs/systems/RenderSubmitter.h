#pragma once
#include "byteCat/ecs/System.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	class RenderSubmitter : public System
	{
	public:
		void onUpdate() override
		{
			for (auto& entity : m_entities)
			{
				auto& transform = m_coordinator->getComponent<Transform>(entity);
				auto& mesh = m_coordinator->getComponent<Mesh>(entity);
				auto& material = m_coordinator->getComponent<Material>(entity);

				glm::mat4 modelMatrix = Math::CreateModelMatrix(transform.position, transform.rotation, transform.scale);
				Renderer::Submit({ mesh.vao, material.shader, material.textures, modelMatrix });
			}
		}
	};
}
