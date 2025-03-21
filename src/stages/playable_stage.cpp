
#include "stages/playable_stage.h"
#include <fmt/format.h>
#include <vector>

#include "entities/entity.h"
#include "game.h"

namespace artifact
{
    PlayableStage::PlayableStage(const char *identifier) : Stage(identifier) {}
    void PlayableStage::startup()
    {
        Stage::startup();

        // Spawn the Player
        this->player = spawn_entity<PlayerEntity>(0, 0);
        pause_screen = std::make_unique<PauseScreen>("pause_screen", this);
    }
    void PlayableStage::draw() const
    {
        if (is_being_destroyed)
            return;

        Stage::draw();
        DrawTextureEx(background, {-1000, -3150}, 0, 2.3, WHITE);
        if (Game::get_instance()->debug_mode)
            debug_draw_colliders();
        for (auto &entity: entities)
        {
            entity->draw();
        }
    }
    void PlayableStage::draw_ui() const
    {
        if (is_paused)
        {
            pause_screen->draw();
        }
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
        if (is_being_destroyed)
            return;
        Stage::update(deltaTime);

        if (IsKeyPressed(KEY_ESCAPE))
            is_paused = !is_paused;

        if (is_paused)
        {
            pause_screen->update(GetMouseX(), GetMouseY());
            return;
        }

        for (const auto &entity: entities)
        {
            entity->update(deltaTime);
        }
    }
    void PlayableStage::destroy()
    {
        if (is_being_destroyed)
            return;
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
    void PlayableStage::pause() { is_paused = true; }
    void PlayableStage::unpause() { is_paused = false; }
} // namespace artifact
