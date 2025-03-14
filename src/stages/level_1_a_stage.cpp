
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
        colliders.emplace_back(-150, 205, block_scale * 9, block_scale, true);
        colliders.emplace_back(-150, -90, block_scale, block_scale * 4, true);
        colliders.emplace_back(-500, 500, block_scale*150, block_scale, [this] { player->set_position(0, 0); });
    }
    void Level1AStage::draw() const
    {
        BeginMode2D(camera);
        PlayableStage::draw();
        DrawRectangle(0, 0, 10, 10, RED);
        EndMode2D();
    }
    void Level1AStage::update(const float deltaTime) { PlayableStage::update(deltaTime); }
    void Level1AStage::destroy() { PlayableStage::destroy(); }
} // namespace artifact
