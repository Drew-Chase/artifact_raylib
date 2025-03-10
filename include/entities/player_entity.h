#pragma once
#include <raylib.h>


#include "entity.h"

namespace artifact
{
    class PlayerEntity final : public Entity
    {
        // Statistics
        int lives = 3;
        int coin = 0;

        // Multipliers
        float sprint_multiplier = 1.5f;
        float jump_multiplier = 1.5f;
        float friction_multiplier = 1.f;
        Camera2D camera = {0};

        void handle_input();

    public:
        void startup() override;
        void draw() override;
        void update(float deltaTime) override;
        void damage(int damage) override;
        void kill() override;
        void jump() override;
        void walk(char direction) override;
    };
} // namespace artifact
