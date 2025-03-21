
#include "stages/level_1_a_stage.h"

namespace artifact
{
    Level1AStage::Level1AStage() : PlayableStage("level_1a") {}
    void Level1AStage::startup()
    {
        PlayableStage::startup();
        music = LoadMusicStream("game/audio/music/level1.ogg");
        music.looping = true;
        SetMusicVolume(music, 0.15f);
        PlayMusicStream(music);

        // Spawn enemies
        // TODO: Spawn enemies

        // Setup features
        // TODO: Create end goal.

        // Initialize Textures
        set_background("game/texture/stages/level_1a/background.png");

        // Create Colliders
        float block_scale = 32 * 2.3;
        float base_x = -150;
        float base_y = 205;

        // Ground
        colliders.emplace_back(base_x - block_scale * 12, base_y - block_scale * 4, block_scale * 11, block_scale, true);
        colliders.emplace_back(base_x, base_y, block_scale * 9, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 9, base_y - block_scale, block_scale, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 10, base_y - block_scale * 2, block_scale * 8, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 19, base_y - block_scale * 5, block_scale * 6, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 25, base_y - block_scale * 4, block_scale, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 26, base_y - block_scale * 3, block_scale * 2, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 28, base_y - block_scale * 2, block_scale * 2, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 30, base_y - block_scale, block_scale * 14, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 44, base_y - block_scale * 2, block_scale * 10, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 86.5, base_y - block_scale * 3, block_scale * 5, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 91.5, base_y - block_scale * 2, block_scale * 9, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 101.5, base_y - block_scale, block_scale * 3, block_scale, true);
        colliders.emplace_back(base_x + block_scale * 118.5, base_y - block_scale * 2, block_scale * 9, block_scale, true);

        // Walls
        colliders.emplace_back(base_x - block_scale * 12.5, base_y - block_scale * 13, block_scale, block_scale * 10, true);
        colliders.emplace_back(base_x - 73.6, base_y - 295, block_scale, block_scale * 4, true);
        colliders.emplace_back(base_x + block_scale * 18, base_y - block_scale * 5, block_scale, block_scale * 3, true);
        colliders.emplace_back(base_x + block_scale * 53, base_y - block_scale, block_scale, block_scale * 10, true);
        colliders.emplace_back(base_x + block_scale * 60, base_y - block_scale * 4, block_scale, block_scale * 8, true);
        colliders.emplace_back(base_x + block_scale * 67, base_y - block_scale * 7, block_scale, block_scale * 8, true);
        colliders.emplace_back(base_x + block_scale * 72.5, base_y - block_scale * 5, block_scale * 3, block_scale * 8, true);
        colliders.emplace_back(base_x + block_scale * 78.5, base_y - block_scale * 4, block_scale, block_scale * 8, true);
        colliders.emplace_back(base_x + block_scale * 82.5, base_y - block_scale * 2, block_scale, block_scale * 8, true);
        colliders.emplace_back(base_x + block_scale * 82.5, base_y - block_scale * 13, block_scale, block_scale * 6, true);
        colliders.emplace_back(base_x + block_scale * 86.5, base_y - block_scale * 2, block_scale, block_scale * 8, true);
        colliders.emplace_back(base_x + block_scale * 100.5, base_y - block_scale * 4, block_scale, block_scale * 3, true);
        colliders.emplace_back(base_x + block_scale * 103.5, base_y, block_scale, block_scale * 3, true);
        colliders.emplace_back(base_x + block_scale * 105.5, base_y - block_scale * 6, block_scale, block_scale * 6, true);
        colliders.emplace_back(base_x + block_scale * 111, base_y - block_scale * 2.5, block_scale, block_scale * 7, true);
        colliders.emplace_back(base_x + block_scale * 111, base_y - block_scale * 13, block_scale, block_scale * 6, true);
        colliders.emplace_back(base_x + block_scale * 127.5, base_y - block_scale * 9, block_scale, block_scale * 7, true);

        // Killnet
        colliders.emplace_back(-500, 500, block_scale * 150, block_scale, [&] { respawn(); });
    }
    void Level1AStage::draw() const
    {
        if (is_being_destroyed)
            return;
        BeginMode2D(camera);
        PlayableStage::draw();
        EndMode2D();
        PlayableStage::draw_ui();
    }
    void Level1AStage::update(const float deltaTime)
    {
        if (is_being_destroyed)
            return;
        PlayableStage::update(deltaTime);
        UpdateMusicStream(music);
    }
    void Level1AStage::destroy()
    {
        if (is_being_destroyed)
            return;
        PlayableStage::destroy();
        UnloadMusicStream(music);
    }
} // namespace artifact
