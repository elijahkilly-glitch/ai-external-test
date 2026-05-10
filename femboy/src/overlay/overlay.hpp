#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"
#include "../hacks/esp.hpp"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

/*
 * ImGui-based overlay menu system
 * Features: Multiple tabs, toggles, sliders, color pickers
 */

namespace overlay
{
    // ============================================================================
    // OVERLAY STATE
    // ============================================================================

    bool show_menu = true;
    bool show_debug = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    // ============================================================================
    // MENU TABS
    // ============================================================================

    enum MenuTab
    {
        TAB_AIMBOT,
        TAB_ESP,
        TAB_MOVEMENT,
        TAB_SETTINGS,
        TAB_DEBUG
    };

    MenuTab current_tab = TAB_AIMBOT;

    // ============================================================================
    // AIMBOT TAB
    // ============================================================================

    void RenderAimbotTab()
    {
        ImGui::Checkbox("##aimbot_enabled", &globals::aimbot::enabled);
        ImGui::SameLine();
        ImGui::Text("Aimbot Enabled");

        ImGui::Separator();

        ImGui::Checkbox("Team Check##aimbot", &globals::aimbot::teamcheck);
        ImGui::Checkbox("Prediction", &globals::aimbot::prediction);
        ImGui::Checkbox("Draw FOV", &globals::aimbot::drawfov);
        ImGui::Checkbox("Disable Out of FOV", &globals::aimbot::disableoutoffov);

        ImGui::Separator();

        ImGui::SliderInt("FOV##aimbot", &globals::aimbot::fov, 10, 500);
        ImGui::SliderInt("Smoothing##aimbot", &globals::aimbot::smoth, 1, 50);
        ImGui::SliderInt("Min Distance", &globals::aimbot::minimumdsitacne, 1, 1000);

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Prediction Settings##aimbot"))
        {
            ImGui::SliderInt("Prediction X", &globals::aimbot::predx, 0, 100);
            ImGui::SliderInt("Prediction Y", &globals::aimbot::predy, 0, 100);
        }

        ImGui::Separator();

        ImGui::Checkbox("##silentaim_enabled", &globals::silentaim::enabled);
        ImGui::SameLine();
        ImGui::Text("Silent Aim");
        ImGui::Checkbox("Team Check##silentaim", &globals::silentaim::teamcheck);
        ImGui::SliderInt("FOV##silentaim", &globals::silentaim::fov, 10, 500);
    }

    // ============================================================================
    // ESP TAB
    // ============================================================================

    void RenderESPTab()
    {
        ImGui::Checkbox("##esp_enabled", &globals::esp::enabled);
        ImGui::SameLine();
        ImGui::Text("ESP Enabled");

        ImGui::Separator();

        ImGui::Checkbox("Boxes", &globals::esp::box);
        ImGui::SameLine();
        ImGui::Checkbox("Box Filled", &globals::esp::boxfilled);

        ImGui::Checkbox("Names", &globals::esp::name);
        ImGui::SameLine();
        ImGui::Checkbox("Distance", &globals::esp::distance);

        ImGui::Checkbox("Health Bars", &globals::esp::health);
        ImGui::SameLine();
        ImGui::Checkbox("Tracers", &globals::esp::tracers);

        ImGui::Checkbox("Skeletons", &globals::esp::skeleton);
        ImGui::SameLine();
        ImGui::Checkbox("Watermark", &globals::esp::watermark);

        ImGui::Checkbox("Team Check##esp", &globals::esp::teamcheck);

        ImGui::Separator();

        ImGui::SliderInt("Max Distance##esp", &globals::esp::maxdistance, 100, 5000);
        ImGui::SliderInt("Font##esp", &globals::esp::font, 0, 5);

        ImGui::Separator();

        if (ImGui::CollapsingHeader("ESP Colors"))
        {
            ImGui::ColorEdit3("Box Color", globals::esp::colors::box);
            ImGui::ColorEdit3("Name Color", globals::esp::colors::name);
            ImGui::ColorEdit3("Distance Color", globals::esp::colors::distance);
            ImGui::ColorEdit3("Health Color", globals::esp::colors::healthbar);
            ImGui::ColorEdit3("Tracer Color", globals::esp::colors::tracers);
            ImGui::ColorEdit3("Skeleton Color", globals::esp::colors::skeleton);
        }
    }

    // ============================================================================
    // MOVEMENT TAB
    // ============================================================================

    void RenderMovementTab()
    {
        ImGui::Checkbox("##flight_enabled", &globals::movement::fly);
        ImGui::SameLine();
        ImGui::Text("Flight");
        ImGui::SliderFloat("Flight Speed", &globals::movement::fspeed, 0.1f, 100.0f);

        ImGui::Separator();

        ImGui::Checkbox("##cframe_enabled", &globals::movement::cframe);
        ImGui::SameLine();
        ImGui::Text("CFrame Movement");
        ImGui::SliderInt("CFrame Speed", &globals::movement::cspeed, 1, 500);

        ImGui::Separator();

        ImGui::Checkbox("##speed_enabled", &globals::movement::speedhack);
        ImGui::SameLine();
        ImGui::Text("Speed Hack");
        ImGui::SliderFloat("Walk Speed", &globals::movement::speedvalue, 0.1f, 200.0f);

        ImGui::Separator();

        ImGui::Checkbox("##noclip_enabled", &globals::movement::noclip);
        ImGui::SameLine();
        ImGui::Text("Noclip");
    }

    // ============================================================================
    // SETTINGS TAB
    // ============================================================================

    void RenderSettingsTab()
    {
        ImGui::Checkbox("Stream Proof", &globals::streamproof);
        ImGui::Checkbox("Hit Log Enabled", &globals::hitlogse);
        ImGui::Checkbox("Hit Sound", &globals::hitsound);

        ImGui::Separator();

        if (ImGui::Button("Reset All Settings", ImVec2(200, 30)))
        {
            // Reset to defaults
            globals::esp::enabled = false;
            globals::aimbot::enabled = false;
            globals::movement::fly = false;
        }
    }

    // ============================================================================
    // DEBUG TAB
    // ============================================================================

    void RenderDebugTab()
    {
        ImGui::Text("Game ID: %llu", globals::gameid);

        if (ImGui::CollapsingHeader("Instance Pointers"))
        {
            ImGui::Text("DataModel: 0x%p", globals::datamodel.self);
            ImGui::Text("Players: 0x%p", globals::players.self);
            ImGui::Text("Workspace: 0x%p", globals::workspace.self);
            ImGui::Text("MouseService: 0x%p", globals::mouse_service.self);
            ImGui::Text("VisualEngine: 0x%p", globals::visualengine.self);
        }

        if (ImGui::CollapsingHeader("Cache Info"))
        {
            ImGui::Text("Cached Players: %zu", hacks::esp::esp_players.size());
        }

        ImGui::Separator();

        if (ImGui::Button("Force Rescan", ImVec2(200, 25)))
        {
            rbx::rescan();
        }
    }

    // ============================================================================
    // MAIN MENU RENDER
    // ============================================================================

    void RenderMenu()
    {
        if (!show_menu) return;

        ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Roblox External - Improved", &show_menu, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::SameLine();
            ImGui::Text("Focused: %s", globals::focused ? "Yes" : "No");

            ImGui::Separator();

            // Tab buttons
            if (ImGui::Button("Aimbot", ImVec2(70, 0))) current_tab = TAB_AIMBOT;
            ImGui::SameLine();
            if (ImGui::Button("ESP", ImVec2(70, 0))) current_tab = TAB_ESP;
            ImGui::SameLine();
            if (ImGui::Button("Movement", ImVec2(70, 0))) current_tab = TAB_MOVEMENT;
            ImGui::SameLine();
            if (ImGui::Button("Settings", ImVec2(70, 0))) current_tab = TAB_SETTINGS;
            ImGui::SameLine();
            if (ImGui::Button("Debug", ImVec2(70, 0))) current_tab = TAB_DEBUG;

            ImGui::Separator();

            // Render current tab
            switch (current_tab)
            {
            case TAB_AIMBOT:
                RenderAimbotTab();
                break;
            case TAB_ESP:
                RenderESPTab();
                break;
            case TAB_MOVEMENT:
                RenderMovementTab();
                break;
            case TAB_SETTINGS:
                RenderSettingsTab();
                break;
            case TAB_DEBUG:
                RenderDebugTab();
                break;
            }

            ImGui::Separator();

            if (ImGui::Button("Exit", ImVec2(100, 30)))
            {
                exit(0);
            }

            ImGui::End();
        }
    }

    // ============================================================================
    // OVERLAY THREAD
    // ============================================================================

    void thread()
    {
        while (true)
        {
            // Check for menu toggle key
            if (GetAsyncKeyState(VK_INSERT) & 0x8000)
            {
                show_menu = !show_menu;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }

            // Update ESP data
            hacks::esp::UpdateESP();

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }
}
