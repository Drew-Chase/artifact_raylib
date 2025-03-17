
#include "stages/level_1_a_stage.h"
#include "entities/player_entity.h"

namespace artifact
{
    Level1AStage::Level1AStage() : PlayableStage("level_1a") {}
    void Level1AStage::startup()
    {
        PlayableStage::startup();

        // Spawn enemies
        // TODO: Spawn enemies

        // Setup features
        // TODO: Create end goal.

        // Initialize Textures
        set_background("game/texture/stages/level_1a/background.png");

        // Create Colliders
        float block_scale = 32 * 2.3;

        // Ground
        colliders.emplace_back(-150 - block_scale * 12, 205 - block_scale * 4, block_scale * 11, block_scale, true);
        colliders.emplace_back(-150, 205, block_scale * 9, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 9, 205 - block_scale, block_scale, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 10, 205 - block_scale * 2, block_scale * 8, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 19, 205 - block_scale * 5, block_scale * 6, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 25, 205 - block_scale * 4, block_scale, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 26, 205 - block_scale * 3, block_scale * 2, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 28, 205 - block_scale * 2, block_scale * 2, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 30, 205 - block_scale, block_scale * 14, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 44, 205 - block_scale * 2, block_scale * 10, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 86.5, 205 - block_scale * 3, block_scale * 5, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 91.5, 205 - block_scale * 2, block_scale * 9, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 101.5, 205 - block_scale, block_scale * 3, block_scale, true);
        colliders.emplace_back(-150 + block_scale * 118.5, 205 - block_scale * 2, block_scale * 9, block_scale, true);

        // Walls
        colliders.emplace_back(-150 - block_scale * 12.5, 205 - block_scale * 13, block_scale, block_scale * 10, true);
        colliders.emplace_back(-223.6, -90, block_scale, block_scale * 4, true);
        colliders.emplace_back(-150 + block_scale * 18, 205 - block_scale * 5, block_scale, block_scale * 3, true);
        colliders.emplace_back(-150 + block_scale * 53, 205 - block_scale, block_scale, block_scale * 10, true);
        colliders.emplace_back(-150 + block_scale * 60, 205 - block_scale * 4, block_scale, block_scale * 8, true);
        colliders.emplace_back(-150 + block_scale * 67, 205 - block_scale * 7, block_scale, block_scale * 8, true);
        colliders.emplace_back(-150 + block_scale * 72.5, 205 - block_scale * 5, block_scale * 3, block_scale * 8, true);
        colliders.emplace_back(-150 + block_scale * 78.5, 205 - block_scale * 4, block_scale, block_scale * 8, true);
        colliders.emplace_back(-150 + block_scale * 82.5, 205 - block_scale * 2, block_scale, block_scale * 8, true);
        colliders.emplace_back(-150 + block_scale * 82.5, 205 - block_scale * 13, block_scale, block_scale * 6, true);
        colliders.emplace_back(-150 + block_scale * 86.5, 205 - block_scale * 2, block_scale, block_scale * 8, true);
        colliders.emplace_back(-150 + block_scale * 100.5, 205 - block_scale * 4, block_scale, block_scale * 3, true);
        colliders.emplace_back(-150 + block_scale * 103.5, 205, block_scale, block_scale * 3, true);
        colliders.emplace_back(-150 + block_scale * 105.5, 205 - block_scale * 6, block_scale, block_scale * 6, true);
        colliders.emplace_back(-150 + block_scale * 111, 205 - block_scale * 2.5, block_scale, block_scale * 7, true);
        colliders.emplace_back(-150 + block_scale * 111, 205 - block_scale * 13, block_scale, block_scale * 6, true);
        colliders.emplace_back(-150 + block_scale * 127.5, 205 - block_scale * 9, block_scale, block_scale * 7, true);

        // Killnet
        colliders.emplace_back(-500, 500, block_scale * 150, block_scale, [&] { respawn(); });
    }
    void Level1AStage::draw() const
    {
        BeginMode2D(camera);
        PlayableStage::draw();
        EndMode2D();
    }
    void Level1AStage::update(const float deltaTime) { PlayableStage::update(deltaTime); }
    void Level1AStage::destroy() { PlayableStage::destroy(); }
} // namespace artifact
