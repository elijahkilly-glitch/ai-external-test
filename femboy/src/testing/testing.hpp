#pragma once
#include "../globals.hpp"
#include "../rbx/classes.hpp"

/*
 * Testing and debugging utilities
 */

namespace testing
{
    // ============================================================================
    // MEMORY TESTING
    // ============================================================================

    void TestMemoryAccess()
    {
        printf("[TEST] Testing memory access...\n");

        // Test reading game ID
        uint64_t game_id = globals::datamodel.GameID();
        printf("[TEST] Game ID: %llu\n", game_id);

        // Test player enumeration
        std::vector<rbx::rinstance> players = globals::players.GetChildren();
        printf("[TEST] Found %zu players\n", players.size());

        for (auto& player : players)
        {
            printf("[TEST] Player: %s\n", player.GetName().c_str());
        }
    }

    // ============================================================================
    // INSTANCE TESTING
    // ============================================================================

    void TestInstanceAccess()
    {
        printf("[TEST] Testing instance access...\n");

        rbx::rinstance workspace = globals::datamodel.FindFirstChildOfClass(("Workspace"));
        printf("[TEST] Workspace found: %s\n", workspace.self ? "Yes" : "No");

        rbx::rinstance camera = workspace.FindFirstChild(("Camera"));
        printf("[TEST] Camera found: %s\n", camera.self ? "Yes" : "No");

        if (camera.self)
        {
            rbx::rvector3 cam_pos = camera.GetCameraPosition();
            printf("[TEST] Camera position: (%.2f, %.2f, %.2f)\n", cam_pos.x, cam_pos.y, cam_pos.z);
        }
    }

    // ============================================================================
    // HUMANOID TESTING
    // ============================================================================

    void TestHumanoidAccess()
    {
        printf("[TEST] Testing humanoid access...\n");

        rbx::rinstance local_player = globals::players.GetLocalPlayer();
        if (!local_player.self)
        {
            printf("[TEST] No local player found\n");
            return;
        }

        rbx::rinstance character = local_player.GetCharacter();
        if (!character.self)
        {
            printf("[TEST] Character not loaded\n");
            return;
        }

        rbx::rinstance humanoid = character.FindFirstChildOfClass(("Humanoid"));
        if (!humanoid.self)
        {
            printf("[TEST] No humanoid found\n");
            return;
        }

        float health = humanoid.Health();
        float max_health = humanoid.MaxHealth();
        printf("[TEST] Health: %.2f / %.2f\n", health, max_health);
    }

    // ============================================================================
    // OFFSET VALIDATION
    // ============================================================================

    void ValidateOffsets()
    {
        printf("[TEST] Validating critical offsets...\n");

        // Print all critical offset values
        printf("[OFFSET] Name: 0x%X\n", rbx::offests::Name);
        printf("[OFFSET] Parent: 0x%X\n", rbx::offests::Parent);
        printf("[OFFSET] Children: 0x%X\n", rbx::offests::Children);
        printf("[OFFSET] GameId: 0x%X\n", rbx::offests::GameId);
        printf("[OFFSET] LocalPlayer: 0x%X\n", rbx::offests::LocalPlayer);
        printf("[OFFSET] Health: 0x%X\n", rbx::offests::Health);
        printf("[OFFSET] Position: 0x%X\n", rbx::offests::Position);
        printf("[OFFSET] CFrame: 0x%X\n", rbx::offests::CFrame);
    }

    // ============================================================================
    // PERFORMANCE TESTING
    // ============================================================================

    void BenchmarkOperations()
    {
        printf("[BENCH] Benchmarking operations...\n");

        // Benchmark player enumeration
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<rbx::rinstance> players = globals::players.GetChildren();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("[BENCH] Player enumeration: %lld us\n", duration.count());

        // Benchmark world to screen
        if (players.size() > 0)
        {
            rbx::rinstance character = players[0].GetCharacter();
            if (character.self)
            {
                rbx::rinstance camera = globals::workspace.FindFirstChild(("Camera"));
                if (camera.self)
                {
                    rbx::rvector3 pos = character.GetPartPosition();
                    start = std::chrono::high_resolution_clock::now();
                    for (int i = 0; i < 1000; i++)
                    {
                        rbx::WorldToScreen(pos, camera.Dimensions(), camera.ViewMatrix());
                    }
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    printf("[BENCH] 1000x WorldToScreen: %lld us (avg: %lld us)\n", duration.count(), duration.count() / 1000);
                }
            }
        }
    }

    // ============================================================================
    // RUN ALL TESTS
    // ============================================================================

    void RunAllTests()
    {
        printf("\n=== RUNNING ALL TESTS ===\n\n");
        ValidateOffsets();
        printf("\n");
        TestMemoryAccess();
        printf("\n");
        TestInstanceAccess();
        printf("\n");
        TestHumanoidAccess();
        printf("\n");
        BenchmarkOperations();
        printf("\n=== TESTS COMPLETE ===\n\n");
    }
}
