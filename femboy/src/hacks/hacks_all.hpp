#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"
#include "../hacks/aimbot.hpp"
#include "../hacks/esp.hpp"
#include "../hacks/movement.hpp"
#include "../cache/cache.hpp"
#include "../hacks/lua.hpp"
#include "../overlay/overlay.hpp"

/*
 * Central configuration file
 * Includes all hack implementations and utilities
 */

// Memory interface instance
MemoryInterface mem(("RobloxPlayerBeta.exe"));

// Include all hack implementations
#include "../hacks/aimbot.hpp"
#include "../hacks/esp.hpp"
#include "../hacks/movement.hpp"
#include "../hacks/lua.hpp"
