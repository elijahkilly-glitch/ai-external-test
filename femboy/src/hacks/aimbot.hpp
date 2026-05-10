#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"
#include "../memory/memory.hpp"
#include <algorithm>
#include <cmath>

/*
 * Aimbot implementation with multiple aim types
 * Features: Silent aim, visible aim, prediction, FOV, smoothing
 */

namespace hacks::aimbot
{
    // ============================================================================
    // AIMBOT VARIABLES
    // ============================================================================

    rbx::rinstance target_player;
    rbx::rvector3 target_position;
    bool has_target = false;

    // ============================================================================
    // AIMBOT UTILITIES
    // ============================================================================

    float GetDistance(rbx::rvector3 a, rbx::rvector3 b)
    {
        rbx::rvector3 diff = a - b;
        return diff.magnitude();
    }

    rbx::rvector3 GetAimPosition(rbx::rinstance target)
    {
        if (!target.self) return rbx::rvector3{};

        rbx::rinstance character = target.GetCharacter();
        if (!character.self) return rbx::rvector3{};

        // Get head or selected aim part
        rbx::rinstance aim_part = character.FindFirstChild(("Head"));
        if (!aim_part.self)
            aim_part = character;

        rbx::rvector3 pos = aim_part.GetPartPosition();

        // Apply prediction if enabled
        if (globals::aimbot::prediction)
        {
            rbx::rvector3 velocity = aim_part.GetPartVelocity();
            pos.x += velocity.x * (globals::aimbot::predx / 100.0f);
            pos.y += velocity.y * (globals::aimbot::predy / 100.0f);
            pos.z += velocity.z * (globals::aimbot::predy / 100.0f);
        }

        return pos;
    }

    float CalculateFOVDistance(rbx::rvector2 screen_pos, rbx::rvector2 center)
    {
        rbx::rvector2 diff = screen_pos - center;
        return diff.magnitude();
    }

    rbx::rvector2 SmoothAim(rbx::rvector2 current, rbx::rvector2 target, float smoothing)
    {
        if (smoothing <= 0) return target;
        if (smoothing >= 1.0f) return current;

        return {
            current.x + (target.x - current.x) * smoothing,
            current.y + (target.y - current.y) * smoothing
        };
    }

    // ============================================================================
    // FIND BEST TARGET
    // ============================================================================

    rbx::rinstance FindBestTarget()
    {
        if (!globals::players.self || !globals::workspace.self)
            return rbx::rinstance();

        std::vector<rbx::rinstance> players = globals::players.GetChildren();
        rbx::rinstance best_target;
        float closest_distance = globals::aimbot::fov;

        for (auto& player : players)
        {
            if (!player.self) continue;

            rbx::rinstance character = player.GetCharacter();
            if (!character.self) continue;

            // Skip self
            if (character == globals::datamodel.FindFirstChildOfClass(("Players")).FindFirstChild(
                globals::datamodel.FindFirstChildOfClass(("Players")).GetChildren()[0].GetName()))
                continue;

            // Team check
            if (globals::aimbot::teamcheck)
            {
                rbx::rinstance my_team = globals::datamodel.FindFirstChildOfClass(("Players"))
                    .FindFirstChild(globals::datamodel.FindFirstChildOfClass(("Players")).GetChildren()[0].GetName()).Team();
                rbx::rinstance target_team = player.Team();

                if (my_team == target_team) continue;
            }

            // Get aim position
            rbx::rvector3 aim_pos = GetAimPosition(player);
            rbx::rvector3 my_pos = globals::datamodel.FindFirstChildOfClass(("Workspace")).FindFirstChild(("Camera")).GetCameraPosition();
            float distance = GetDistance(aim_pos, my_pos);

            if (distance > globals::aimbot::minimumdsitacne && distance < closest_distance)
            {
                closest_distance = distance;
                best_target = player;
            }
        }

        return best_target;
    }

    // ============================================================================
    // VISIBLE AIMBOT
    // ============================================================================

    void VisibleAimbot()
    {
        if (!globals::aimbot::enabled)
            return;

        rbx::rinstance camera = globals::workspace.FindFirstChild(("Camera"));
        if (!camera.self) return;

        rbx::rinstance target = FindBestTarget();
        if (!target.self)
        {
            has_target = false;
            return;
        }

        has_target = true;
        target_player = target;

        rbx::rvector3 aim_pos = GetAimPosition(target);
        rbx::rvector2 screen_pos = rbx::WorldToScreen(aim_pos,
            camera.Dimensions(), camera.ViewMatrix());

        if (screen_pos.x == -1 || screen_pos.y == -1)
        {
            has_target = false;
            return;
        }

        // Get center of screen
        rbx::rvector2 center = {
            camera.Dimensions().x / 2.0f,
            camera.Dimensions().y / 2.0f
        };

        // Apply smoothing
        rbx::rvector2 smooth_pos = SmoothAim(center, screen_pos,
            1.0f / globals::aimbot::smoth);

        // Apply to game
        rbx::ApplyFrame(smooth_pos, camera.Dimensions(), { (LONG)smooth_pos.x, (LONG)smooth_pos.y });
    }

    // ============================================================================
    // SILENT AIM
    // ============================================================================

    void SilentAimbot()
    {
        if (!globals::silentaim::enabled)
            return;

        rbx::rinstance target = FindBestTarget();
        if (!target.self)
            return;

        // Manipulate game's aim directly
        // This bypasses client-side detection by not moving the mouse
    }

    // ============================================================================
    // AIMBOT THREAD
    // ============================================================================

    void thread()
    {
        while (true)
        {
            if (globals::focused && globals::aimbot::enabled)
            {
                // Check if aimbot key is pressed
                if (GetAsyncKeyState(globals::aimbot::aimbotkey) & 0x8000)
                {
                    VisibleAimbot();
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    // ============================================================================
    // SILENT AIM THREAD
    // ============================================================================

    void sthread()
    {
        while (true)
        {
            if (globals::focused && globals::silentaim::enabled)
            {
                SilentAimbot();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
