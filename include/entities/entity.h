#pragma once
#include <raylib.h>

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
        Rectangle bounds = {0, 0, 1, 2};
        Vector2 position = {0.0f, 0.0f};
        PlayableStage *owner = nullptr;


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
        virtual bool has_hit_obstacle();
        virtual void debug_draw_colliders();
        Rectangle get_bounds() const;
    };
} // namespace artifact
