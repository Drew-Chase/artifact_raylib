#pragma once
#include <raymath.h>

namespace artifact
{
    class PlayableStage;
    class Entity
    {
    protected:
        // Statistics
        int max_health = 5;
        int health = max_health;
        int attack_damage = 1;
        bool is_on_ground = true;
        float gravity_multiplier = 1.f;

        // Multipliers
        float walk_speed_multiplier = 1.f;

        Vector2 position = {0.0f, 0.0f};
        PlayableStage *owner = nullptr;

        virtual void startup();
        virtual void destroy();

    public:
        virtual ~Entity() = default;
        virtual void draw();
        virtual void update(float deltaTime);
        virtual void damage(int damage);
        virtual void kill();
        void spawn(int x, int y, PlayableStage *owner);
        virtual void jump();
        virtual void walk(char direction);
        virtual void goto_point(Vector2 point);
    };
} // namespace artifact
