
#include "stages/playable_stage.h"
#include <fmt/format.h>
#include <vector>

#include "entities/entity.h"

namespace artifact
{
    PlayableStage::PlayableStage(const char *identifier) : Stage(identifier) {}
    void PlayableStage::startup()
    {
        Stage::startup();
        // Spawn the Player
        // this->player = spawn_entity<PlayerEntity>(-150 + 32 * 2.3 * 118.5, 205 - 32 * 2.3 * 4);
        this->player = spawn_entity<PlayerEntity>(0, 0);
    }
    void PlayableStage::draw() const
    {

        Stage::draw();
        DrawTextureEx(background, {-1000, -3150}, 0, 2.3, WHITE);
        for (auto &entity: entities)
        {
            entity->draw();
        }
        debug_draw_colliders();
    }
    void PlayableStage::debug_draw_colliders() const
    {
        for (const auto collider: colliders)
        {
            DrawRectangleLinesEx(collider.bounds, 4, collider.is_blocking ? RED : BLUE);
        }
    }
    void PlayableStage::update(const float deltaTime)
    {
        Stage::update(deltaTime);

        for (const auto &entity: entities)
        {
            entity->update(deltaTime);
        }
    }
    void PlayableStage::destroy()
    {
        Stage::destroy();
        entities.clear();
        UnloadTexture(background);
    }
    bool PlayableStage::is_entity_colliding(const Entity *entity) const { return Collider::is_entity_colliding(entity, colliders); }
    Collider PlayableStage::get_collider_at(const int x, const int y, const bool blocking_only) const { return Collider::get_collider_at(x, y, colliders, blocking_only); }
    std::vector<Collider> PlayableStage::get_colliders_closest_to(const int x, const int y, const bool blocking_only) const { return Collider::get_colliders_closest_to(x, y, colliders, blocking_only); }
    std::vector<Collider> PlayableStage::get_blocking_colliders() const { return Collider::get_blocking_colliders(colliders); }
    void PlayableStage::set_background(const char *resource_location) { this->background = LoadTexture(resource_location); }
    Texture2D *PlayableStage::get_background() { return &background; }
    void PlayableStage::respawn()
    {
        camera.target = {0, 0};
        player->set_position(0, 0);
    }
} // namespace artifact
