#include "entities/entity.h"

namespace artifact
{
    void Entity::draw() {}
    void Entity::update(const float deltaTime) {}
    void Entity::damage(int damage) {}
    void Entity::kill() {}
    void Entity::spawn(const int x, const int y, PlayableStage *owner)
    {
        this->owner = owner;
        this->position = Vector2{static_cast<float>(x), static_cast<float>(y)};
        this->startup();
    }
    void Entity::startup() {}
    void Entity::goto_point(Vector2 point) {}
    bool Entity::has_hit_obstacle() { return false; }
    void Entity::debug_draw_colliders() { DrawRectangleLinesEx(bounds, 1, GREEN); }
    Rectangle Entity::get_bounds() const { return bounds; }
    void Entity::destroy() {}
} // namespace artifact
