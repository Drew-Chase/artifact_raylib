
#include "entities/demon_bat_entity.h"

namespace artifact
{
    void DemonBatEntity::startup()
    {
        EnemyEntity::startup();
        idle_sheet = new SpriteSheet("game/texture/entities/demon_bat/idle%d.PNG", 7, 10);
    }
    void DemonBatEntity::draw()
    {
        EnemyEntity::draw();
        if (idle_sheet != nullptr)
            idle_sheet->draw(this->position, 2);
    }
    void DemonBatEntity::update(const float delta_time)
    {
        EnemyEntity::update(delta_time);
        if (idle_sheet)
            idle_sheet->update(delta_time);
    }
    void DemonBatEntity::destroy() { EnemyEntity::destroy(); }
    void DemonBatEntity::damage(const int damage, const Direction direction) { EnemyEntity::damage(damage, direction); }
    void DemonBatEntity::kill() { EnemyEntity::kill(); }
} // namespace artifact
