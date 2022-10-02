#pragma once

/*  Welcome to the:
 *  ------------------------------------------------------------------
 *							 BYTECAT ENGINE
 *  ------------------------------------------------------------------
 *
 *	Import this header file to make use of the ByteCat engine.
 *	Every code from the ByteCat Engine is inside the BC namespace.
 *
 *	This graphics engine is created by:
 *	Menno Bil
 *
 *	Link to the GitHub Repository:
 *	https://github.com/CodingWithMenno/ByteCat
*/

#include "byteCat/app/Application.h"
#include "byteCat/app/Layer.h"
#include "byteCat/app/Time.h"

#include "byteCat/Log.h"

#include "byteCat/inputs/events/Event.h"
#include "byteCat/inputs/events/ApplicationEvent.h"
#include "byteCat/inputs/events/KeyEvent.h"
#include "byteCat/inputs/events/MouseEvent.h"
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/MouseCodes.h"
#include "byteCat/inputs/Gamepad.h"
#include "byteCat/inputs/Input.h"

#include "byteCat/graphics/Window.h"
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/components/ArrayBuffer.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"
#include "byteCat/graphics/components/FrameBuffer.h"

#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/Renderer2D.h"
#include "byteCat/graphics/renderer/Renderable.h"
#include "byteCat/graphics/renderer/RenderPass.h"
#include "byteCat/graphics/renderer/renderPasses/ForwardPass.h"

#include "byteCat/ecs/systems/CameraSystem.h"
#include "byteCat/ecs/systems/RenderSubmitter.h"
#include "byteCat/ecs/systems/LightSystem.h"
#include "byteCat/ecs/Entity.h"
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/SceneManager.h"
#include "byteCat/ecs/components/Transform.h"
#include "byteCat/ecs/components/Material.h"
#include "byteCat/ecs/components/Mesh.h"
#include "byteCat/ecs/components/Light.h"

#include "byteCat/utils/Math.h"
#include "byteCat/utils/Utility.h"
#include "byteCat/utils/FileIO.h"

#ifdef BC_PLATFORM_PC
	#include <imgui.h>
#endif

// -- Start of the engine --
#include "byteCat/EntryPoint.h"
// -----------------------