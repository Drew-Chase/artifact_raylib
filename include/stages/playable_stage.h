#pragma once
#include <memory>
#include <raylib.h>
#include "collider.h"
#include "entities/player_entity.h"
#include "stage.h"
#include "ui/menus/pause_screen.h"
namespace artifact
{

    class Entity;
    class PlayableStage : public Stage
    {
    protected:
        Texture2D background;
        PlayerEntity *player;
        std::vector<std::unique_ptr<Entity>> entities;
        std::vector<Collider> colliders;
        bool is_paused = false;
        virtual void draw_ui() const;

    public:
        std::unique_ptr<PauseScreen> pause_screen;
        Camera2D camera{};
        explicit PlayableStage(const char *identifier);
        template<typename T>
            requires std::derived_from<T, Entity>
        T *spawn_entity(int x, int y)
        {
            auto entity = std::make_unique<T>();
            T *raw_ptr = entity.get();
            entity->spawn(x, y, this);
            entities.push_back(std::move(entity));
            return raw_ptr;
        }

        void startup() override;
        void draw() const override;
        void debug_draw_colliders() const;
        void update(float deltaTime) override;
        void destroy() override;
        bool is_entity_colliding(const Entity *entity) const;
        Collider get_collider_at(int x, int y, bool blocking_only = true) const;
        std::vector<Collider> get_colliders_closest_to(int x, int y, bool blocking_only = true) const;
        std::vector<Collider> get_blocking_colliders() const;
        void set_background(const char *resource_location);
        Texture2D *get_background();
        void respawn();
        void pause();
        void unpause();
    };
} // namespace artifact
