#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"
#include <cmath>

/*
 * Movement hacks implementation
 * Features: CFrame teleport, flight, speed, noclip
 */

namespace hacks::movement
{
    // ============================================================================
    // MOVEMENT VARIABLES
    // ============================================================================

    rbx::rvector3 flight_direction;
    bool is_flying = false;

    // ============================================================================
    // FLIGHT HACK
    // ============================================================================

    void Flight()
    {
        if (!globals::movement::fly)
            return;

        rbx::rinstance local_player = globals::players.GetLocalPlayer();
        if (!local_player.self) return;

        rbx::rinstance character = local_player.GetCharacter();
        if (!character.self) return;

        rbx::rinstance root_part = character.FindFirstChild(("HumanoidRootPart"));
        if (!root_part.self) return;

        // Get camera direction
        rbx::rinstance camera = globals::workspace.FindFirstChild(("Camera"));
        if (!camera.self) return;

        rbx::rvector3 cam_pos = camera.GetCameraPosition();
        rbx::rmatrix3 cam_rot = camera.GetCameraRotation();

        // Calculate movement direction based on input
        rbx::rvector3 movement = { 0, 0, 0 };

        if (GetAsyncKeyState('W') & 0x8000) movement.z -= globals::movement::fspeed;
        if (GetAsyncKeyState('S') & 0x8000) movement.z += globals::movement::fspeed;
        if (GetAsyncKeyState('A') & 0x8000) movement.x -= globals::movement::fspeed;
        if (GetAsyncKeyState('D') & 0x8000) movement.x += globals::movement::fspeed;
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) movement.y += globals::movement::fspeed;
        if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) movement.y -= globals::movement::fspeed;

        // Apply camera rotation to movement
        rbx::rvector3 new_pos = cam_pos + movement;

        // Create CFrame and apply
        rbx::CFrame cf(new_pos);
        root_part.SetCFrame(cf);
    }

    // ============================================================================
    // CFRAME TELEPORT
    // ============================================================================

    void CFrameMove()
    {
        if (!globals::movement::cframe)
            return;

        rbx::rinstance local_player = globals::players.GetLocalPlayer();
        if (!local_player.self) return;

        rbx::rinstance character = local_player.GetCharacter();
        if (!character.self) return;

        rbx::rinstance root_part = character.FindFirstChild(("HumanoidRootPart"));
        if (!root_part.self) return;

        rbx::rinstance humanoid = character.FindFirstChildOfClass(("Humanoid"));
        if (!humanoid.self) return;

        // Get current position
        rbx::rvector3 current_pos = root_part.GetPartPosition();
        rbx::rvector3 movement = { 0, 0, 0 };

        // Get movement input
        if (GetAsyncKeyState('W') & 0x8000) movement.z -= globals::movement::cspeed / 100.0f;
        if (GetAsyncKeyState('S') & 0x8000) movement.z += globals::movement::cspeed / 100.0f;
        if (GetAsyncKeyState('A') & 0x8000) movement.x -= globals::movement::cspeed / 100.0f;
        if (GetAsyncKeyState('D') & 0x8000) movement.x += globals::movement::cspeed / 100.0f;

        // Apply movement
        rbx::rvector3 new_pos = current_pos + movement;
        rbx::CFrame cf(new_pos);
        root_part.SetCFrame(cf);
    }

    // ============================================================================
    // SPEED HACK
    // ============================================================================

    void SpeedHack()
    {
        if (!globals::movement::speedhack)
            return;

        rbx::rinstance local_player = globals::players.GetLocalPlayer();
        if (!local_player.self) return;

        rbx::rinstance character = local_player.GetCharacter();
        if (!character.self) return;

        rbx::rinstance humanoid = character.FindFirstChildOfClass(("Humanoid"));
        if (!humanoid.self) return;

        // Set walk speed
        humanoid.SetWalkSpeed(globals::movement::speedvalue);
    }

    // ============================================================================
    // NOCLIP HACK
    // ============================================================================

    void Noclip()
    {
        if (!globals::movement::noclip)
            return;

        rbx::rinstance local_player = globals::players.GetLocalPlayer();
        if (!local_player.self) return;

        rbx::rinstance character = local_player.GetCharacter();
        if (!character.self) return;

        // Disable collision for all parts
        std::vector<rbx::rinstance> parts = character.GetChildren();
        for (auto& part : parts)
        {
            if (part.self)
            {
                part.SetPartCanCollide(false);
            }
        }
    }

    // ============================================================================
    // MOVEMENT THREAD
    // ============================================================================

    void thread()
    {
        while (true)
        {
            if (globals::focused)
            {
                Flight();
                CFrameMove();
                SpeedHack();
                Noclip();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}
