#include "entities/entity.h"

#include "game.h"

namespace artifact
{
    void Entity::draw()
    {
        if (Game::get_instance()->debug_mode)
            debug_draw_colliders();
    }
    void Entity::update(const float deltaTime) {}
    void Entity::damage(const int damage)
    {
        if (health <= 0)
        {
            kill();
        } else
        {
            health -= damage;
        }
    }
    void Entity::kill() { health = 0; }
    void Entity::spawn(const int x, const int y, PlayableStage *owner)
    {
        this->owner = owner;
        this->position = Vector2{static_cast<float>(x), static_cast<float>(y)};
        this->startup();
    }
    void Entity::set_position(const int x, const int y) { this->position = Vector2{static_cast<float>(x), static_cast<float>(y)}; }
    void Entity::startup() {}
    bool Entity::has_hit_obstacle() { return false; }
    void Entity::debug_draw_colliders() { DrawRectangleLinesEx(bounds, 1, GREEN); }
    Rectangle Entity::get_bounds() const { return bounds; }
    void Entity::destroy() {}
} // namespace artifact
