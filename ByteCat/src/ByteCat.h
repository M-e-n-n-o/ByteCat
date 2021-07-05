#pragma once

/*
	Import this header file to make use of the BC engine.
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
#include "byteCat/input/Input.h"

#include "byteCat/utils/Math.h"

#include "byteCat/render/textures/Texture.h"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/render/vertex-object/Buffer.h"
#include "byteCat/render/vertex-object/VertexArray.h"

#include "byteCat/entity-system/GameObject.h"
#include "byteCat/entity-system/Mesh.h"

// --Start of the engine--
#include "byteCat/EntryPoint.h"
// -----------------------