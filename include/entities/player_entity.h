#pragma once

namespace artifact
{
    class PlayerEntity:public Entity
    {
        // Statistics
        int lives = 3;
        int coin = 0

        // Multipliers
        float sprint_multiplier = 1.5f;
        float jump_multiplier = 1.5f;
        float gravity_multiplier = 1.f;
        float friction_multiplier = 1.f;
    };
} // namespace artifact
