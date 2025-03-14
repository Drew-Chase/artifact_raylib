#include "entities/player_entity.h"
#include <cmath>
#include <fmt/format.h>
#include <raymath.h>
#include "game.h"
#include "stages/playable_stage.h"

namespace artifact
{
    void PlayerEntity::startup()
    {
        Entity::startup();
        owner->camera.target = this->position;
        owner->camera.zoom = 1.0f;
        owner->camera.rotation = 0;
    }

    void PlayerEntity::draw()
    {
        Entity::draw();
        DrawRectanglePro({position.x, position.y, bounds.x, bounds.y}, {0, 0}, 0, BLUE);
        DrawText(fmt::format("Player Pos: X{}, Y{}", this->position.x, this->position.y).c_str(), 0, 50, 16, WHITE);
        DrawText(fmt::format("Grounded: {}, VVel: {:.1f}, HVel: {:.1f}", is_grounded ? "true" : "false", vertical_velocity, horizontal_velocity).c_str(), 0, 70, 16, WHITE);
    }

    void PlayerEntity::update(const float deltaTime)
    {
        if (!IsWindowReady())
            return;
        Entity::update(deltaTime);

        // Handle user input for movement
        handle_input(deltaTime);

        // Check collisions
        check_ground_collision();

        // Apply physics
        apply_gravity(deltaTime);
        apply_horizontal_movement(deltaTime);

        // Update camera
        UpdateCameraCenterSmoothFollow(deltaTime);
    }

    void PlayerEntity::apply_gravity(const float deltaTime)
    {
        // Apply gravity to vertical velocity
        vertical_velocity -= gravity * deltaTime;

        // Apply vertical velocity to position
        position.y -= vertical_velocity * deltaTime;
    }

    void PlayerEntity::apply_horizontal_movement(const float deltaTime)
    {
        // Apply horizontal velocity to position
        position.x += horizontal_velocity * deltaTime;

        // Apply friction based on ground state
        const float friction = is_grounded ? ground_friction : air_friction;

        // Slow down the player over time
        if (std::abs(horizontal_velocity) > 0.1f)
        {

            // Make sure we don't overshoot and flip direction
            if (const float slowdown = friction * deltaTime * std::copysign(1.0f, horizontal_velocity); std::abs(slowdown) > std::abs(horizontal_velocity))
                horizontal_velocity = 0.0f;
            else
                horizontal_velocity -= slowdown;
        } else
        {
            horizontal_velocity = 0.0f;
        }
    }

    void PlayerEntity::check_ground_collision()
    {
        const float feet_y = position.y + bounds.y;

        // Check if we found a ground collider
        if (const Collider ground_collider = owner->get_collider_at(position.x + bounds.x / 2, feet_y); ground_collider != EMPTY_COLLIDER)
        {
            // If we're falling (negative velocity) and hit something
            if (vertical_velocity <= 0)
            {
                // Set the player on top of the collider
                position.y = ground_collider.bounds.y - bounds.y;
                vertical_velocity = 0;
                is_grounded = true;
                is_jumping = false;
            }
        } else
        {
            // Not touching ground
            is_grounded = false;
        }
    }

    void PlayerEntity::damage(const int damage) { Entity::damage(damage); }

    void PlayerEntity::kill() { Entity::kill(); }

    void PlayerEntity::jump()
    {
        // Only allow jumping if the player is on the ground
        if (is_grounded && !is_jumping)
        {
            vertical_velocity = jump_force;
            is_grounded = false;
            is_jumping = true;
        }
    }

    void PlayerEntity::handle_input(const float deltaTime)
    {
        const ControlsSettings *controls = Game::get_instance()->controls_settings;

        // Handle sprint toggle
        if (IsKeyDown(controls->movement_sprint))
            sprinting = controls->toggle_sprint ? !sprinting : true;
        else if (IsKeyUp(controls->movement_sprint) && !controls->toggle_sprint)
            sprinting = false;

        // Handle jump input
        if (IsKeyPressed(controls->movement_jump))
            jump();

        // Calculate modifiers
        const float control_multiplier = is_grounded ? 1.0f : air_control;
        const float speed_multiplier = (sprinting ? sprint_multiplier : walk_speed_multiplier) * control_multiplier;

        // Calculate target speed based on input
        float target_speed = 0.0f;

        if (IsKeyDown(controls->movement_right))
            target_speed = walk_speed * speed_multiplier;
        else if (IsKeyDown(controls->movement_left))
            target_speed = -walk_speed * speed_multiplier;
        else if (is_grounded)
            // Only set target_speed to 0 if on the ground
            // When in mid-air, we'll keep the current horizontal_velocity
            target_speed = 0.0f;
        else
            // In mid-air with no input, keep current velocity (don't apply acceleration)
            return;

        // Apply acceleration towards the target speed
        if (std::abs(target_speed - horizontal_velocity) > 0.1f)
        {
            const float direction = target_speed > horizontal_velocity ? 1.0f : -1.0f;
            const float acc = acceleration * control_multiplier * deltaTime;

            // Ensure we don't overshoot the target speed
            if (std::abs(acc) > std::abs(target_speed - horizontal_velocity))
                horizontal_velocity = target_speed;
            else
                horizontal_velocity += acc * direction;
        }
    }

    void PlayerEntity::UpdateCameraCenterSmoothFollow(const float delta) const
    {
        constexpr float minEffectLength = 10;
        owner->camera.offset = (Vector2) {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        const Vector2 diff = Vector2Subtract(position, owner->camera.target);

        if (const float length = Vector2Length(diff); length > minEffectLength)
        {
            constexpr float fractionSpeed = 0.9f;
            constexpr float minSpeed = 10;
            const float speed = fmaxf(fractionSpeed * length, minSpeed);
            owner->camera.target = Vector2Add(owner->camera.target, Vector2Scale(diff, speed * delta / length));
        }
    }
} // namespace artifact
