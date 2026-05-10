#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"
#include <deque>
#include <ctime>

/*
 * Caching system for efficient player/object tracking
 */

namespace rbx::cache
{
    // ============================================================================
    // HIT LOG SYSTEM
    // ============================================================================

    struct HitLogEntry
    {
        std::string player_name;
        float damage;
        std::time_t hit_time;
        int duration_ms = 3000;
    };

    std::deque<HitLogEntry> hit_log;

    void AddHitLog(const std::string& player_name, float damage)
    {
        HitLogEntry entry;
        entry.player_name = player_name;
        entry.damage = damage;
        entry.hit_time = std::time(nullptr);

        hit_log.push_back(entry);

        // Limit log size
        if (hit_log.size() > 20)
            hit_log.pop_front();
    }

    // ============================================================================
    // PLAYER CACHE
    // ============================================================================

    struct LocalPlayer
    {
        rbx::rinstance aim;
        rbx::rinstance hc_aim;
        rbx::rinstance rh_aim;
        rbx::rinstance kh_aim;
    };

    LocalPlayer localplayer;

    void UpdateCache()
    {
        rbx::rinstance local = globals::players.GetLocalPlayer();
        if (!local.self) return;

        rbx::rinstance character = local.GetCharacter();
        if (!character.self) return;

        // Cache body parts for faster access
        localplayer.aim = character.FindFirstChild(("Head"));
        localplayer.hc_aim = character.FindFirstChild(("UpperTorso"));
        localplayer.rh_aim = character.FindFirstChild(("RightHand"));
        localplayer.kh_aim = character.FindFirstChild(("LeftHand"));
    }

    // ============================================================================
    // CACHE THREAD
    // ============================================================================

    void thread()
    {
        while (true)
        {
            UpdateCache();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
