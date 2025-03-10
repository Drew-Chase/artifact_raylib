
#include "entities/player_entity.h"

namespace artifact
{
    void PlayerEntity::startup()
    {
        Entity::startup();
        camera.target = this->position;
        camera.zoom = 1.0f;
        camera.rotation = 0;
    }
    void PlayerEntity::draw() { Entity::draw(); }
    void PlayerEntity::update(const float deltaTime) { Entity::update(deltaTime); }
    void PlayerEntity::damage(const int damage) { Entity::damage(damage); }
    void PlayerEntity::kill() { Entity::kill(); }
    void PlayerEntity::jump() { Entity::jump(); }
    void PlayerEntity::walk(const char direction) { Entity::walk(direction); }
    void PlayerEntity::handle_input()
    {
    }
} // namespace artifact
