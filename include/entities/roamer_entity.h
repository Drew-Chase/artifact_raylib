#pragma once
#include "../sprite_sheet.h"
#include "enemy_entity.h"

namespace artifact
{
    class RoamerEntity final : public EnemyEntity
    {
        Vector2 start_position;
        Vector2 end_position;
        SpriteSheet* walk_sheet = nullptr;
        SpriteSheet* attack_sheet = nullptr;
        unsigned int attacking_frames = 0;
        bool is_facing_right = true;
    public:
        explicit RoamerEntity(Vector2 start_position, Vector2 end_position);
        void startup() override;
        void destroy() override;
        void draw() override;
        void damage(int damage) override;
        void kill() override;
        void update(float deltaTime) override;
        void debug_draw_colliders() override;
    };
} // namespace artifact
