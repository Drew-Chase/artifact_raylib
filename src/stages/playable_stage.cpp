
#include "stages/playable_stage.h"
#include <fmt/format.h>
#include <vector>

#include "entities/entity.h"
#include "game.h"

namespace artifact
{
    PlayableStage::PlayableStage(const char *identifier) :
        Stage(identifier) {}
    void PlayableStage::startup()
    {
        Stage::startup();
        spawn_entities();

        level_open_overlay = new LevelOpenOverlay(this, 1.f);
        pause_screen = std::make_unique<PauseScreen>(this);
        death_screen = std::make_unique<DeathScreen>(this);
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
        this->player->draw_stats();
        level_open_overlay->draw();

        if (player->is_dead())
            death_screen->draw();
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
    void PlayableStage::update(const float delta_time)
    {
        if (is_being_destroyed)
            return;
        Stage::update(delta_time);

        level_open_overlay->update(delta_time);
        if (IsKeyPressed(KEY_ESCAPE))
            is_paused = !is_paused;
        if (is_paused)
        {
            if (this->peek_zindex() != pause_screen.get())
                this->push_to_zindex(pause_screen.get());
            return;
        }

        if (this->peek_zindex() == pause_screen.get())
            this->remove_from_zindex(pause_screen.get());


        for (const auto &entity: entities)
        {
            entity->update(delta_time);
            entity->check_entity_collisions(entities);
        }

        check_collider_overlaps();
    }
    void PlayableStage::update(const int mouse_x, const int mouse_y)
    {
        Stage::update(mouse_x, mouse_y);
        if (player->is_dead())
            death_screen->update(mouse_x, mouse_y);
        if (is_paused)
            pause_screen->update(mouse_x, mouse_y);
    }
    void PlayableStage::destroy()
    {
        if (is_being_destroyed)
            return;
        Stage::destroy();
        entities.clear();
        UnloadTexture(background);
    }
    Collider PlayableStage::get_collider_at(const int x, const int y, const bool blocking_only) const { return Collider::get_collider_at(x, y, colliders, blocking_only); }
    std::vector<Collider> PlayableStage::get_colliders_closest_to(const int x, const int y, const bool blocking_only) const { return Collider::get_colliders_closest_to(x, y, colliders, blocking_only); }
    std::vector<Collider> PlayableStage::get_blocking_colliders() const { return Collider::get_blocking_colliders(colliders); }
    void PlayableStage::set_background(const char *resource_location) { this->background = LoadTexture(resource_location); }
    Texture2D *PlayableStage::get_background() { return &background; }
    void PlayableStage::pause() { is_paused = true; }
    void PlayableStage::unpause() { is_paused = false; }
    Vector2 PlayableStage::get_spawn_position() const { return {0, 0}; }
    void PlayableStage::respawn()
    {
        player->respawn();
    }
    PlayerEntity *PlayableStage::get_player()
    {
        return player;
    }

    void PlayableStage::check_collider_overlaps()
    {
        for (const auto &entity: entities)
        {
            const Rectangle entityBounds = {
                    entity->get_position().x,
                    entity->get_position().y,
                    entity->get_width(),
                    entity->get_height()};

            for (auto &collider: colliders)
            {
                if (!collider.is_blocking && CheckCollisionRecs(entityBounds, collider.bounds))
                {
                    collider.overlap(entity);
                }
            }
        }
    }
    void PlayableStage::register_collider(const int x, const int y, const int width, const int height, const std::function<void(Entity *)> &on_entity_overlap)
    {
        colliders.emplace_back(x, y, width, height, on_entity_overlap);
    }

} // namespace artifact
