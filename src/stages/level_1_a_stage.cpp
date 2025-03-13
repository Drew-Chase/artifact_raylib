
#include "stages/level_1_a_stage.h"
#include "entities/player_entity.h"

namespace artifact
{
    Level1AStage::Level1AStage() : PlayableStage("level_1a") {}
    void Level1AStage::startup()
    {
        PlayableStage::startup();

        // Spawn the Player
        spawn_entity<PlayerEntity>(0, 0);

        // Spawn enemies
        // TODO: Spawn enemies

        // Setup features
        // TODO: Create end goal.

        // Initialize Textures
        set_background("game/texture/stages/level_1a/background.png");
    }
    void Level1AStage::draw() const { PlayableStage::draw(); }
    void Level1AStage::update(const float deltaTime) { PlayableStage::update(deltaTime); }
    void Level1AStage::destroy() { PlayableStage::destroy(); }
} // namespace artifact
