#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"
#include "../memory/memory.hpp"
#include <algorithm>

/*
 * ESP (wallhack) implementation
 * Features: Boxes, names, distance, health bars, skeletons, tracers, chams
 */

namespace hacks::esp
{
    // ============================================================================
    // ESP STRUCTURES
    // ============================================================================

    struct ESPPlayer
    {
        rbx::rinstance player;
        rbx::rvector2 screen_pos;
        float distance;
        std::string name;
        float health;
        float max_health;
        rbx::rvector3 world_pos;
    };

    std::vector<ESPPlayer> esp_players;

    // ============================================================================
    // ESP UTILITIES
    // ============================================================================

    float GetDistance(rbx::rvector3 a, rbx::rvector3 b)
    {
        rbx::rvector3 diff = a - b;
        return diff.magnitude();
    }

    bool WorldToScreen(rbx::rvector3 world, rbx::rvector2& screen_out)
    {
        rbx::rinstance camera = globals::workspace.FindFirstChild(("Camera"));
        if (!camera.self) return false;

        screen_out = rbx::WorldToScreen(world, camera.Dimensions(), camera.ViewMatrix());
        return screen_out.x != -1 && screen_out.y != -1;
    }

    // ============================================================================
    // ESP RENDERING (Placeholder for ImGui)
    // ============================================================================

    void DrawBox(ImDrawList* draw_list, rbx::rvector2 top_left, rbx::rvector2 bottom_right, ImU32 color, float thickness = 1.0f)
    {
        if (!globals::esp::box) return;

        ImVec2 tl = { top_left.x, top_left.y };
        ImVec2 br = { bottom_right.x, bottom_right.y };

        if (globals::esp::boxfilled)
        {
            draw_list->AddRectFilled(tl, br, color);
        }
        else
        {
            draw_list->AddRect(tl, br, color, 0.0f, ImDrawCornerFlags_All, thickness);
        }
    }

    void DrawHealthBar(ImDrawList* draw_list, rbx::rvector2 pos, float health, float max_health)
    {
        if (!globals::esp::health || max_health == 0) return;

        float health_percentage = health / max_health;
        ImVec2 bar_top = { pos.x - 2, pos.y };
        ImVec2 bar_bottom = { pos.x - 2, pos.y + 50 };
        ImVec2 health_end = { pos.x - 2, pos.y + (50 * (1.0f - health_percentage)) };

        // Background
        draw_list->AddRectFilled(bar_top, bar_bottom, IM_COL32(0, 0, 0, 255));

        // Health bar
        ImU32 health_color = IM_COL32(10, 250, 34, 255);
        if (health_percentage < 0.5f)
            health_color = IM_COL32(255, 165, 0, 255);
        if (health_percentage < 0.25f)
            health_color = IM_COL32(255, 0, 0, 255);

        draw_list->AddRectFilled(health_end, bar_bottom, health_color);
    }

    void DrawText(ImDrawList* draw_list, rbx::rvector2 pos, const std::string& text, ImU32 color)
    {
        if (text.empty()) return;
        ImVec2 text_pos = { pos.x, pos.y };
        draw_list->AddText(text_pos, color, text.c_str());
    }

    void DrawTracer(ImDrawList* draw_list, rbx::rvector2 screen_pos)
    {
        if (!globals::esp::tracers) return;

        rbx::rvector2 center = { globals::workspace.FindFirstChild(("Camera")).Dimensions().x / 2.0f,
                                globals::workspace.FindFirstChild(("Camera")).Dimensions().y / 2.0f };

        ImVec2 from = { center.x, center.y };
        ImVec2 to = { screen_pos.x, screen_pos.y };

        ImU32 color = IM_COL32(
            (ImU8)(globals::esp::colors::tracers[0] * 255),
            (ImU8)(globals::esp::colors::tracers[1] * 255),
            (ImU8)(globals::esp::colors::tracers[2] * 255),
            255
        );

        draw_list->AddLine(from, to, color, 1.5f);
    }

    void DrawSkeleton(ImDrawList* draw_list, rbx::rvector3 world_pos)
    {
        if (!globals::esp::skeleton) return;
        // Skeleton drawing would require bone positions
        // Implementation depends on bone offset data
    }

    // ============================================================================
    // ESP MAIN FUNCTION
    // ============================================================================

    void UpdateESP()
    {
        if (!globals::esp::enabled)
            return;

        esp_players.clear();

        if (!globals::players.self || !globals::workspace.self)
            return;

        rbx::rinstance camera = globals::workspace.FindFirstChild(("Camera"));
        if (!camera.self) return;

        rbx::rvector3 camera_pos = camera.GetCameraPosition();
        std::vector<rbx::rinstance> players = globals::players.GetChildren();

        for (auto& player : players)
        {
            if (!player.self) continue;

            rbx::rinstance character = player.GetCharacter();
            if (!character.self) continue;

            // Team check
            if (globals::esp::teamcheck)
            {
                // TODO: Implement team checking
            }

            rbx::rvector3 pos = character.GetPartPosition();
            rbx::rvector2 screen_pos;

            if (!WorldToScreen(pos, screen_pos))
                continue;

            float distance = GetDistance(pos, camera_pos);

            if (distance > globals::esp::maxdistance)
                continue;

            ESPPlayer esp_player;
            esp_player.player = player;
            esp_player.screen_pos = screen_pos;
            esp_player.distance = distance;
            esp_player.name = player.GetName();
            esp_player.world_pos = pos;

            // Get health if humanoid exists
            rbx::rinstance humanoid = character.FindFirstChildOfClass(("Humanoid"));
            if (humanoid.self)
            {
                esp_player.health = humanoid.Health();
                esp_player.max_health = humanoid.MaxHealth();
            }

            esp_players.push_back(esp_player);
        }
    }

    void RenderESP(ImDrawList* draw_list)
    {
        if (!globals::esp::enabled) return;

        for (const auto& player : esp_players)
        {
            ImU32 color = IM_COL32(
                (ImU8)(globals::esp::colors::box[0] * 255),
                (ImU8)(globals::esp::colors::box[1] * 255),
                (ImU8)(globals::esp::colors::box[2] * 255),
                255
            );

            // Draw box
            rbx::rvector2 box_size = { 40, 60 };
            rbx::rvector2 top_left = { player.screen_pos.x - box_size.x / 2, player.screen_pos.y - box_size.y / 2 };
            rbx::rvector2 bottom_right = { top_left.x + box_size.x, top_left.y + box_size.y };
            DrawBox(draw_list, top_left, bottom_right, color);

            // Draw name
            if (globals::esp::name)
                DrawText(draw_list, { top_left.x, top_left.y - 15 }, player.name, color);

            // Draw distance
            if (globals::esp::distance)
            {
                char distance_str[32];
                sprintf_s(distance_str, "[%.1fm]", player.distance);
                DrawText(draw_list, { top_left.x, top_left.y + box_size.y + 5 }, distance_str, color);
            }

            // Draw health bar
            if (globals::esp::health)
                DrawHealthBar(draw_list, { top_left.x - 5, top_left.y }, player.health, player.max_health);

            // Draw tracer
            DrawTracer(draw_list, player.screen_pos);
        }
    }
}
