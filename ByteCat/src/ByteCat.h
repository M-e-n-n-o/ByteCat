#pragma once

/*
	Import this header file to make use of the BC engine.

	Do not use the "CORE" namespace when using the engine.
	This will give you access to core functionalities which are
	meant to only be called by the ByteCat engine itself.
*/

#include "byteCat/Application.h"
#include "byteCat/Log.h"

#include "byteCat/input/KeyCodes.h"
#include "byteCat/input/MouseCodes.h"
#include "byteCat/input/Input.h"

// --Start of the engine--
#include "byteCat/EntryPoint.h"
// -----------------------