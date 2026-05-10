#pragma once

// Standard Library
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <array>

// Windows
#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>

// DirectX
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ImGui
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/imgui/imgui_impl_win32.h"

// FreeType
#include "../ext/freetype/ft2build.h"
#include FT_FREETYPE_H

// Project Headers
#include "xorstr.hpp"
#include "globals.hpp"
#include "rbx/classes.hpp"
#include "rbx/offsets.hpp"
