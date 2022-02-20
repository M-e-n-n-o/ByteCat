#pragma once
#include "byteCat/ecs/SceneManager.h"
#include "byteCat/ecs/System.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	class RenderSubmitter : public System
	{
	private:
		inline static glm::vec3 m_cameraPos;
		
	public:
		static void onRenderRenderable(const Renderable& renderable)
		{
			renderable.shader->loadVector3("_CameraPos", m_cameraPos);
		}
		
		void onUpdate() override
		{
			Entity camera = SceneManager::GetActiveScene()->getMainCamera();			
			m_cameraPos = m_coordinator->getComponent<Transform>(camera).position;
			
			for (auto& entity : m_entities)
			{
				auto& transform = m_coordinator->getComponent<Transform>(entity);
				auto& mesh = m_coordinator->getComponent<Mesh>(entity);
				auto& material = m_coordinator->getComponent<Material>(entity);

				glm::mat4 modelMatrix = Math::CreateModelMatrix(transform.position, transform.rotation, transform.scale);
				Renderer::Submit({ mesh.vao, material.shader, material.textures, modelMatrix, onRenderRenderable });
			}
		}
	};
}
