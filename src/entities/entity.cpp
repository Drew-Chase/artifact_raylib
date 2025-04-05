#include "entities/entity.h"

#include "Direction.h"
#include "entities/player_entity.h"
#include "game.h"

namespace artifact
{
    void Entity::startup()
    {
        if (!collider)
        {
            collider = std::make_unique<Collider>(position.x, position.y, width, height, [this](Entity *entity) { this->on_entity_collision(entity); });
            collider->set_owner(this);
        }
    }
    void Entity::draw()
    {
        if (Game::get_instance()->debug_mode)
            debug_draw_colliders();
    }
    void Entity::update(const float delta_time)
    {
        if (collider)
        {
            collider->bounds = {position.x, position.y, width, height};
        }
    }
    void Entity::damage(const int damage, const Direction direction)
    {
        health -= damage;
        if (health <= 0)
            kill();
    }
    void Entity::kill() { health = 0; }
    void Entity::spawn(const int x, const int y, PlayableStage *owner)
    {
        this->owner = owner;
        this->position = Vector2{static_cast<float>(x), static_cast<float>(y)};
        this->startup();
    }
    void Entity::set_position(const float x, const float y)
    {
        this->position = Vector2{x, y};
    }
    Vector2 Entity::get_position() const { return position; }
    void Entity::debug_draw_colliders() { DrawRectangleLinesEx(Rectangle{position.x, position.y, width, height}, 1, GREEN); }
    void Entity::destroy()
    {
        is_being_destroyed = true;
    }
    bool Entity::is_colliding_with(const Entity *other) const
    {
        if (!collider || !other || !other->collider)
            return false;

        return CheckCollisionRecs({position.x, position.y, width, height}, {other->position.x, other->position.y, other->width, other->height});
    }
    void Entity::check_entity_collisions(const std::vector<Entity *> &entities)
    {
        for (const auto &other_entity: entities)
        {
            if (other_entity == this) // Don't check collision with self
                continue;

            if (is_colliding_with(other_entity) && collider && other_entity && other_entity->collider)
            {
                // Call overlap on both entities
                collider->overlap(other_entity);
                other_entity->collider->overlap(this);
            }
        }
    }
    bool Entity::is_dead() const { return health <= 0; }
    float Entity::get_width() const
    {
        return width;
    }
    float Entity::get_height() const
    {
        return height;
    }
    void Entity::on_entity_collision(Entity *entity)
    {
        if (entity == nullptr || is_dead())
            return;

        if (auto *player = dynamic_cast<PlayerEntity *>(entity))
        {
            player->damage(this->attack_damage, player->get_position().x > this->position.x ? Direction::RIGHT : Direction::LEFT);
        }
    }
} // namespace artifact
