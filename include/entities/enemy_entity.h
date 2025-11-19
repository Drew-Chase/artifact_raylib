#pragma once
#include "entity.h"

namespace artifact
{
    class EnemyEntity : public Entity
    {
    public:
        void debug_draw_colliders() override
        {
            DrawRectangleLinesEx(collider->bounds, 2, PURPLE);
        }
    };
} // namespace artifact
