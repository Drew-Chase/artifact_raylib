
#include "../../include/stages/playable_stage.h"

#include <stdexcept>

#include "entities/entity.h"

namespace artifact
{
    void PlayableStage::startup() { Stage::startup(); }
    void PlayableStage::draw() const
    {
        Stage::draw();
        for (auto &entity: entities)
        {
            entity->draw();
        }
    }
    void PlayableStage::update(const float deltaTime) const
    {
        Stage::update(deltaTime);
        for (auto &entity: entities)
        {
            entity->update(deltaTime);
        }
    }
    void PlayableStage::destroy()
    {
        Stage::destroy();
        entities.clear();
    }
} // namespace artifact
