#pragma once
#include <memory>
#include <raylib.h>
#include "collider.h"
#include "entities/player_entity.h"
#include "stage.h"
#include "ui/menus/death_screen.h"
#include "ui/menus/pause_screen.h"
#include "ui/overlays/level_open_overlay.h"
namespace artifact
{

    class Entity;
    class PlayableStage : public Stage
    {
    protected:
        PlayerEntity *player;
        Texture2D background;
        std::vector<Entity*> entities;
        std::vector<Collider> colliders;
        bool is_paused = false;
        virtual void draw_ui() const;

    public:
        LevelOpenOverlay *level_open_overlay;
        std::unique_ptr<PauseScreen> pause_screen;
        std::unique_ptr<DeathScreen> death_screen;
        Camera2D camera{};
        explicit PlayableStage(const char *identifier);


        template<typename T, typename... Args>
            requires std::derived_from<T, Entity>
        T *spawn_entity(int x, int y, Args &&...args)
        {
            T *raw_ptr = new T(std::forward<Args>(args)...);
            raw_ptr->spawn(x, y, this);
            entities.push_back(raw_ptr);
            return raw_ptr;
        }

        void startup() override;
        void draw() const override;
        void debug_draw_colliders() const;
        void update(float delta_time) override;
        void update(int mouse_x, int mouse_y) override;

        void destroy() override;
        Collider get_collider_at(int x, int y, bool blocking_only = true) const;
        std::vector<Collider> get_colliders_closest_to(int x, int y, bool blocking_only = true) const;
        std::vector<Collider> get_blocking_colliders() const;
        void set_background(const char *resource_location);
        Texture2D *get_background();
        void pause();
        void unpause();
        virtual Vector2 get_spawn_position() const;
        virtual void spawn_entities(){}
        virtual void respawn();
        virtual PlayerEntity* get_player();
    };
} // namespace artifact
