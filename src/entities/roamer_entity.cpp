
#include "entities/roamer_entity.h"

namespace artifact
{
    RoamerEntity::RoamerEntity(const Vector2 start_position, const Vector2 end_position) : start_position(start_position), end_position(end_position) {}
    void RoamerEntity::startup()
    {
        EnemyEntity::startup();
        walk_sheet = new SpriteSheet("game/texture/entities/roaming_slime/walk%d.png", 8, 13);
        attack_sheet = new SpriteSheet("game/texture/entities/roaming_slime/attack%d.png", 8, 8);
    }
    void RoamerEntity::destroy() { EnemyEntity::destroy(); }
    void RoamerEntity::draw()
    {
        EnemyEntity::draw();
        if (walk_sheet != nullptr)
            walk_sheet->draw(this->position, 2);
    }
    void RoamerEntity::update(const float deltaTime)
    {
        EnemyEntity::update(deltaTime);
        if (walk_sheet)
            walk_sheet->update(deltaTime);
        if (is_facing_right)
        {
            if (position.x < end_position.x)
            {
                position.x += 100 * deltaTime;
            }else
            {
                is_facing_right = false;
                if (walk_sheet)
                    walk_sheet->set_flipped(true);
            }

        } else
        {
            if (position.x > start_position.x)
            {
                position.x -= 100 * deltaTime;
            }else
            {
                is_facing_right = true;
                if (walk_sheet)
                    walk_sheet->set_flipped(false);
            }
        }
    }

    void RoamerEntity::damage(const int damage) { EnemyEntity::damage(damage); }
    void RoamerEntity::kill() { EnemyEntity::kill(); }
    void RoamerEntity::debug_draw_colliders()
    {
        EnemyEntity::debug_draw_colliders();
        DrawRectangleLinesEx({start_position.x, start_position.y, 64, 64}, 1, BLUE);
        DrawRectangleLinesEx({end_position.x, end_position.y, 64, 64}, 1, BLUE);
    }
} // namespace artifact
