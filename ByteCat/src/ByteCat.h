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

#include "byteCat/input/events/m_event.h"
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
#include "byteCat/graphics/renderer/Renderer.h"

// --Start of the engine--
#include "byteCat/EntryPoint.h"
// -----------------------