# Roblox External Hack - Improved Edition

**A fully featured, improved Roblox external with modern code organization, better offsets, and enhanced features.**

## Features

- ✅ **ESP** (Boxes, Names, Distance, Health bars, Skeletons)
- ✅ **Aimbot** (Silent aim, Visible aim, FOV circle, Prediction)
- ✅ **Triggerbot** (Automatic shooting)
- ✅ **Movement Hacks** (CFrame teleport, Flight)
- ✅ **Player Manipulation** (Speed, Jump, Size)
- ✅ **UI Menu** (ImGui-based overlay)
- ✅ **Hit logs** and Sound effects
- ✅ **Team check** and Filters

## BUILD INSTRUCTIONS

### Prerequisites
- Visual Studio 2022 or later
- Windows 10/11 x64
- Latest DirectX SDK

### Setup

1. Clone the repository
2. Open `femboy.sln` in Visual Studio
3. Configure project settings:
   - Set to **Release x64**
   - Ensure Windows SDK is properly installed
   - Link required libraries (d3d11, dxgi, etc.)

4. Build the solution

### Usage

1. Launch Roblox and join a game
2. Run the compiled external
3. Press **INSERT** to open the menu
4. Configure hacks as needed
5. Press **INSERT** again to close

## Project Structure

```
femboy/
├── src/
│   ├── rbx/              # Roblox memory/classes
│   │   ├── offsets.hpp   # All 276+ offsets (organized)
│   │   ├── classes.hpp   # Roblox instance classes
│   │   └── cache.hpp     # Object caching
│   ├── hacks/            # Feature implementations
│   │   ├── aimbot.cpp    # Aimbot logic
│   │   ├── esp.cpp       # ESP rendering
│   │   ├── movement.cpp  # Movement hacks
│   │   └── ...
│   ├── memory/           # Memory utilities
│   ├── overlay/          # UI/Rendering
│   ├── cache/            # Caching system
│   ├── entry.cpp         # Main entry point
│   ├── globals.hpp       # Global state
│   └── includes.h        # Common includes
├── ext/                  # External libraries
│   ├── imgui/           # ImGui UI framework
│   └── freetype/        # Font rendering
└── femboy.vcxproj       # Visual Studio project
```

## Improvements Over Original

- **Better Code Organization**: Offsets sorted by category
- **Enhanced Memory Access**: Safer pointer dereferences
- **Improved UI**: Better menu layout and controls
- **Latest Offsets**: Updated to 276+ offsets (v-bf6344c9c23446bf)
- **Documentation**: Better comments and structure
- **Performance**: Optimized rendering and memory loops
- **Stability**: Better error handling and validation

## Keyboard Shortcuts

| Key | Function |
|-----|----------|
| **INSERT** | Toggle Menu |
| **Mouse4** | Aimbot Toggle (configurable) |
| **E** | Triggerbot (configurable) |
| **SPACE** | Flight (in movement menu) |

## Configuration

All settings are stored in `globals.hpp` and can be modified via the in-game menu:

- ESP colors and styles
- Aimbot sensitivity and FOV
- Movement speed and type
- Audio settings
- Team check toggle

## Disclaimer

⚠️ **This tool is for educational purposes only.** Use at your own risk. Roblox actively detects and bans external tools. We are not responsible for any account bans or consequences.

## Credits

- Original by itxusername
- Improved and maintained by elijahkilly-glitch
- ImGui UI framework
- FreeType font rendering

---

**Last Updated**: 2026-05-10
