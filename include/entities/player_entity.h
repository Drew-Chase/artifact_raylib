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

    protected:
        void startup() override;

    };
} // namespace artifact
