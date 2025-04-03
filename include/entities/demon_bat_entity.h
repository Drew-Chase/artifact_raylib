#pragma once
#include "enemy_entity.h"
#include "sprite_sheet.h"

namespace artifact {
class DemonBatEntity final : public EnemyEntity {
    SpriteSheet* idle_sheet = nullptr;
public:
    void startup() override;
    void destroy() override;
    void draw() override;
    void update(float delta_time) override;
    void damage(int damage, Direction direction) override;
    void kill() override;
};
} // artifact
