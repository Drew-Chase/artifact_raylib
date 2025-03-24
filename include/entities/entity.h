#pragma once
#include <memory>
#include <raylib.h>

#include "collider.h"

namespace artifact
{
    class PlayableStage;
    class Entity
    {
    protected:
        // Statistics
        int max_health = 1;
        int health = max_health;
        int attack_damage = 1;
        bool is_on_ground = true;
        float gravity_multiplier = 1.f;

        // Multipliers
        float walk_speed_multiplier = 1.f;

        // Entity variables
        float width = 0;
        float height = 0;
        Vector2 position = {0.0f, 0.0f};

        PlayableStage *owner = nullptr;
        std::unique_ptr<Collider> collider;
        virtual void on_entity_collision(Entity *entity);


    public:
        virtual ~Entity() = default;
        virtual void startup();
        virtual void destroy();
        virtual void draw();
        virtual void update(float deltaTime);
        virtual void damage(int damage);
        virtual void kill();
        void spawn(int x, int y, PlayableStage *owner);
        virtual void set_position(int x, int y);
        virtual void debug_draw_colliders();
        bool is_colliding_with(const Entity *other) const;
        void check_entity_collisions(const std::vector<Entity *> &entities);
    };
} // namespace artifact
