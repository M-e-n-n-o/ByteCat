#pragma once

/*
	Precompiled header file
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "byteCat/Log.h"
#include "byteCat/Platform.h"

#ifdef BC_PLATFORM_WINDOWS
	#include <Windows.h>
#endif