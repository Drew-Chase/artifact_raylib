
#include "entities/demon_bat_entity.h"

namespace artifact
{
    void DemonBatEntity::startup()
    {
        width = height = 48;
        EnemyEntity::startup();
        idle_sheet = new SpriteSheet("game/texture/entities/demon_bat/idle%d.PNG", 7, 10);
        idle_sheet->set_flipped(true);
    }
    void DemonBatEntity::draw()
    {
        if (is_dead())
            return;
        EnemyEntity::draw();
        if (idle_sheet != nullptr)
            idle_sheet->draw(this->position, 2);
    }
    void DemonBatEntity::update(const float delta_time)
    {
        if (is_dead())
            return;
        if (idle_sheet)
            idle_sheet->update(delta_time);

        if (collider)
        {
            collider->bounds = {position.x - width / 4, position.y - height / 2, width, height};
        }
    }
    void DemonBatEntity::destroy() { EnemyEntity::destroy(); }
    void DemonBatEntity::damage(const int damage, const Direction direction) { EnemyEntity::damage(damage, direction); }
    void DemonBatEntity::kill() { EnemyEntity::kill(); }
} // namespace artifact
