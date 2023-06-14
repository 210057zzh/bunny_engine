// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#define NOMINMAX
#include <windows.h>
#include <d3d11.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <deque>
#include <mutex>
#include <memory>
#include <array>

#include "DbgAssert.h"