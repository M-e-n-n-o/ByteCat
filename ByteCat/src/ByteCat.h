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

#include "byteCat/Log.h"

#include "byteCat/input/events/Event.h"
#include "byteCat/input/events/ApplicationEvent.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/input/events/MouseEvent.h"
#include "byteCat/input/KeyCodes.h"
#include "byteCat/input/MouseCodes.h"
#include "byteCat/input/Gamepad.h"
#include "byteCat/input/Input.h"

#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/components/ArrayBuffer.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"
#include "byteCat/graphics/components/FrameBuffer.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/renderer/submissionRenderers/SimpleRenderer.h"

#include "byteCat/ecs/systems/CameraSystem.h"
#include "byteCat/ecs/systems/RenderSubmitter.h"
#include "byteCat/ecs/Entity.h"
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/Behaviour.h"
#include "byteCat/ecs/SceneManager.h"
#include "byteCat/ecs/components/Transform.h"
#include "byteCat/ecs/components/Material.h"
#include "byteCat/ecs/components/Mesh.h"

#include "byteCat/utils/Math.h"

#include "imgui/imgui.h"

// --Start of the engine--
#include "byteCat/EntryPoint.h"
// -----------------------