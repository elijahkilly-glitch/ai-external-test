# Enhanced Build Instructions

## Prerequisites
- Visual Studio 2022 or later (Professional/Community)
- Windows 10/11 x64
- Latest Windows SDK (v10.0.22000 or later)
- DirectX SDK (included with Visual Studio)

## Step-by-Step Setup

### 1. Clone & Open Project
```bash
git clone https://github.com/elijahkilly-glitch/ai-external-test.git
cd ai-external-test
```

Open `femboy.sln` in Visual Studio 2022

### 2. Configure Project Settings

#### Platform & Configuration
- Select **Release** configuration
- Select **x64** platform
- Go to Project Properties (Alt+F7)

#### C++ Settings
- Preprocessor Definitions: Add `_CRT_SECURE_NO_WARNINGS`
- Runtime Library: Multi-threaded DLL (/MD)
- Optimization: Maximize Speed (/O2)

#### Linker Settings
- Input -> Additional Dependencies:
  - d3d11.lib
  - dxgi.lib
  - d3dcompiler.lib
  - psapi.lib
  - ws2_32.lib

### 3. Include Paths
Ensure these paths are in your project:
- `$(ProjectDir)src/`
- `$(ProjectDir)src/ext/imgui/`
- `$(ProjectDir)src/ext/freetype/`
- `$(ProjectDir)include/`

### 4. Build
```
Build -> Build Solution (F7)
```
Output: `\x64\Release\femboy.exe`

### 5. Run
1. Launch Roblox and join any game
2. Run the compiled `femboy.exe`
3. Press **INSERT** to open menu
4. Configure and enable hacks

## Features

### Aimbot
- **Visible Aimbot**: Automatic aim lock with smoothing
- **Silent Aim**: No visible mouse movement
- **Prediction**: Lead targets based on velocity
- **FOV Circle**: Limit aim to specific field of view
- **Smoothing**: Control aim speed (1-50)
- **Minimum Distance**: Don't aim at close targets

### ESP (Wallhack)
- **Boxes**: 2D boxes around players
- **Names**: Player names above heads
- **Distance**: Show distance in studs/meters
- **Health Bars**: HP indicators
- **Tracers**: Lines from center to players
- **Skeletons**: Bone visualization
- **Team Check**: Friendly player filtering
- **Max Distance**: ESP render distance limit

### Movement
- **Flight**: Free movement in 3D space
- **CFrame**: Teleport-based movement
- **Speed**: Modify walk speed
- **Noclip**: Pass through walls
- **Customizable keybinds**

### UI Menu
- **5 Tabs**: Aimbot, ESP, Movement, Settings, Debug
- **Color Pickers**: Customize all ESP colors
- **Sliders**: Fine-tune all settings
- **Debug Info**: View memory addresses and FPS
- **Real-time Updates**: Changes apply instantly

## Keyboard Shortcuts

| Key | Function |
|-----|----------|
| **INSERT** | Toggle Menu |
| **W/A/S/D** | Move (Flight/CFrame) |
| **SPACE** | Up (Flight) |
| **CTRL** | Down (Flight) |
| **Right Mouse** | Aimbot (Configurable) |
| **Left Mouse** | Silent Aim (Configurable) |

## File Structure

```
femboy/
├── src/
│   ├── rbx/
│   │   ├── offsets.hpp        # 276+ offsets
│   │   ├── classes.hpp        # Roblox class definitions
│   │   └── cache.hpp          # Object caching
│   ├── hacks/
│   │   ├── aimbot.hpp         # Aimbot logic
│   │   ├── esp.hpp            # ESP rendering
│   │   ├── movement.hpp       # Movement hacks
│   │   ├── lua.hpp            # Lua callbacks
│   │   └── hacks_all.hpp      # Include all
│   ├── memory/
│   │   └── memory.hpp         # Safe memory access
│   ├── overlay/
│   │   └── overlay.hpp        # ImGui menu system
│   ├── cache/
│   │   └── cache.hpp          # Player/object cache
│   ├── testing/
│   │   └── testing.hpp        # Testing utilities
│   ├── entry.cpp              # Main entry point
│   ├── globals.hpp            # Global configuration
│   ├── includes.h             # Common includes
│   └── xorstr_improved.hpp    # String encoding
├── ext/
│   ├── imgui/                 # UI framework
│   └── freetype/              # Font rendering
└── femboy.vcxproj             # Visual Studio project
```

## Testing

The project includes comprehensive testing utilities:

```cpp
testing::TestMemoryAccess();      // Verify game access
testing::TestInstanceAccess();    // Test Roblox objects
testing::TestHumanoidAccess();    // Test character access
testing::ValidateOffsets();       // Check offset values
testing::BenchmarkOperations();   // Performance metrics
testing::RunAllTests();           // Run all tests
```

## Important Notes

⚠️ **Disclaimer**: This tool is for educational purposes only
- Roblox actively detects external tools
- Using this may result in permanent account ban
- Use at your own risk
- Do not use on accounts you care about

## Troubleshooting

### Issue: Memory access errors
- **Solution**: Run as Administrator, wait for Roblox to fully load

### Issue: Offsets out of date
- **Solution**: Update `femboy/src/rbx/offsets.hpp` with new offsets

### Issue: Menu doesn't appear
- **Solution**: Ensure ImGui is properly linked and Roblox window is focused

### Issue: Hacks don't work
- **Solution**: Check `console.log` in overlay debug tab, verify Roblox version matches

## Credits

- Original by itxusername
- Improved by elijahkilly-glitch
- ImGui framework
- FreeType font library

---

**Last Updated**: 2026-05-10
**Version**: 2.0 (Improved Edition)
