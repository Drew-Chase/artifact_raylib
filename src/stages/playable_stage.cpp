
#include "stages/playable_stage.h"
#include <stdexcept>
#include <vector>
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
    void PlayableStage::debug_draw_colliders() const
    {
        for (const auto [bounds, blocking]: colliders)
        {
            DrawRectangleLinesEx(bounds, 1, blocking ? RED : BLUE);
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
    bool PlayableStage::is_entity_colliding(const Entity *entity) const { return Collider::is_entity_colliding(entity, colliders); }
    Collider PlayableStage::get_collider_at(const int x, const int y, const bool blocking_only) const { return Collider::get_collider_at(x, y, colliders, blocking_only); }
    std::vector<Collider> PlayableStage::get_colliders_closest_to(const int x, const int y, const bool blocking_only) const { return Collider::get_colliders_closest_to(x, y, colliders, blocking_only); }
    std::vector<Collider> PlayableStage::get_blocking_colliders() const { return Collider::get_blocking_colliders(colliders); }
} // namespace artifact
