
#include "../../include/stages/level_1_a_stage.h"

#include "entities/player_entity.h"

namespace artifact {
    void Level1AStage::startup()
    {
        PlayableStage::startup();
        spawn_entity<PlayerEntity>(0, 0);
    }
    void Level1AStage::draw() const { PlayableStage::draw(); }
    void Level1AStage::update(const float deltaTime) const { PlayableStage::update(deltaTime); }
    void Level1AStage::destroy() { PlayableStage::destroy(); }
} // artifact