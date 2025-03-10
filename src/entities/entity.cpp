
#include "entities/entity.h"

namespace artifact
{
    void Entity::draw() {}
    void Entity::update(float deltaTime) {}
    void Entity::damage(int damage) {}
    void Entity::kill() {}
    void Entity::spawn(const int x, const int y, PlayableStage *owner)
    {
        this->owner = owner;
        this->position = Vector2{static_cast<float>(x), static_cast<float>(y)};
        this->startup();
    }
    void Entity::startup() {}
    void Entity::jump() {}
    void Entity::walk(char direction) {}
    void Entity::goto_point(Vector2 point) {}
    void Entity::destroy() {}
} // namespace artifact
