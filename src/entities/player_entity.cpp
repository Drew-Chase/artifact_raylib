
#include "entities/player_entity.h"
#include "game.h"

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
    void PlayerEntity::update(const float deltaTime)
    {
        Entity::update(deltaTime);
        handle_input(deltaTime);
    }
    void PlayerEntity::damage(const int damage) { Entity::damage(damage); }
    void PlayerEntity::kill() { Entity::kill(); }
    void PlayerEntity::jump()
    {
        Entity::jump();
    }
    void PlayerEntity::handle_input(const float deltaTime)
    {
        const ControlsSettings *controls = Game::get_instance()->controls_settings;
        if (IsKeyDown(controls->movement_sprint))
            sprinting = controls->toggle_sprint ? !sprinting : true;
        else if (IsKeyUp(controls->movement_sprint) && !controls->toggle_sprint)
            sprinting = false;

        if (IsKeyPressed(controls->movement_jump))
            jump();
        if (IsKeyPressed(controls->movement_right))
            this->position.x += 10 * deltaTime * walk_speed_multiplier;
        else if (IsKeyPressed(controls->movement_left))
            this->position.x -= 10 * deltaTime;
    }
} // namespace artifact
