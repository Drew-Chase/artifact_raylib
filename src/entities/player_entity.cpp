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
        owner->camera.zoom = 1;
        owner->camera.rotation = 0;

        // Load sprite sheets
        SpriteSheet idle_sheet("game/texture/entities/player/idle%d.png", 9, 8);
    }

    void PlayerEntity::draw()
    {
        Entity::draw();
        // DrawRectanglePro({position.x, position.y, bounds.x, bounds.y}, {0, 0}, 0, BLUE);
        // DrawText(fmt::format("Player Pos: X{}, Y{}", this->position.x, this->position.y).c_str(), 0, 50, 16, WHITE);
        // DrawText(fmt::format("Grounded: {}, VVel: {:.1f}, HVel: {:.1f}", is_grounded ? "true" : "false", vertical_velocity, horizontal_velocity).c_str(), 0, 70, 16, WHITE);

        // Draw animations
        if (is_grounded)
        {
            if (horizontal_velocity == 0)
            {
                idle_sheet.draw(position);
            }
        }
    }

    void PlayerEntity::update(const float deltaTime)
    {
        if (!IsWindowReady())
            return;
        Entity::update(deltaTime);

        handle_input(deltaTime);
        check_collision();
        apply_gravity(deltaTime);
        apply_horizontal_movement(deltaTime);

        idle_sheet.update(deltaTime);

        UpdateCameraCenterSmoothFollow(deltaTime);
    }

    void PlayerEntity::apply_gravity(const float deltaTime)
    {
        vertical_velocity -= gravity * deltaTime;
        position.y -= vertical_velocity * deltaTime;
    }

    void PlayerEntity::apply_horizontal_movement(const float deltaTime)
    {
        position.x += horizontal_velocity * deltaTime;

        const float friction = is_grounded ? ground_friction : air_friction;

        if (std::abs(horizontal_velocity) > 0.1f)
        {

            if (const float slowdown = friction * deltaTime * std::copysign(1.0f, horizontal_velocity); std::abs(slowdown) > std::abs(horizontal_velocity))
                horizontal_velocity = 0.0f;
            else
                horizontal_velocity -= slowdown;
        } else
        {
            horizontal_velocity = 0.0f;
        }
    }

    void PlayerEntity::check_collision()
    {
        enum EdgeType
        {
            LEFT,
            RIGHT,
            TOP,
            BOTTOM
        };

        struct CheckPoint
        {
            float x_percent; // Percentage of width
            float y_percent; // Percentage of height
            EdgeType edge;
        };

        const std::vector<CheckPoint> check_points = {// Bottom edge points (for ground detection)
                                                      {0.2f, 1.0f, BOTTOM},
                                                      {0.5f, 1.0f, BOTTOM},
                                                      {0.8f, 1.0f, BOTTOM},

                                                      // Left edge points
                                                      {0.0f, 0.3f, LEFT},
                                                      {0.0f, 0.6f, LEFT},

                                                      // Right edge points
                                                      {1.0f, 0.3f, RIGHT},
                                                      {1.0f, 0.6f, RIGHT},

                                                      // Top edge points
                                                      {0.2f, 0.0f, TOP},
                                                      {0.5f, 0.0f, TOP},
                                                      {0.8f, 0.0f, TOP}};

        const bool was_grounded = is_grounded;
        is_grounded = false;

        float highest_ground = std::numeric_limits<float>::lowest();

        for (const auto &[x_percent, y_percent, edge]: check_points)
        {
            const int check_x = static_cast<int>(position.x + bounds.x * x_percent);
            const int check_y = static_cast<int>(position.y + bounds.y * y_percent);

            std::vector<Collider> nearby_colliders = owner->get_colliders_closest_to(check_x, check_y, false);

            if (nearby_colliders.empty())
                continue;

            for (Collider &collider: nearby_colliders)
            {
                if (!CheckCollisionPointRec({static_cast<float>(check_x), static_cast<float>(check_y)}, collider.bounds))
                    continue;

                collider.overlap();
                if (!collider.is_blocking)
                    continue;
                switch (edge)
                {
                    case BOTTOM:
                        if (vertical_velocity <= 0)
                        {
                            if (collider.bounds.y > highest_ground)
                            {
                                highest_ground = collider.bounds.y;
                            }
                            is_grounded = true;
                            jump_count = 0;
                        }
                        break;

                    case LEFT:
                        if (horizontal_velocity < 0)
                        {
                            position.x = collider.bounds.x + collider.bounds.width;
                            horizontal_velocity = 0;
                        }
                        break;

                    case RIGHT:
                        if (horizontal_velocity > 0)
                        {
                            position.x = collider.bounds.x - bounds.x;
                            horizontal_velocity = 0;
                        }
                        break;

                    case TOP:
                        if (vertical_velocity < 0)
                        {
                            position.y = collider.bounds.y + collider.bounds.height;
                            vertical_velocity = 0;
                        }
                        break;
                }

                break;
            }
        }

        if (is_grounded)
        {
            position.y = highest_ground - bounds.y;
            vertical_velocity = 0;
        }

        if (!was_grounded && is_grounded)
        {
            // Landing effects could go here (sound, particles, etc.)
        }
    }

    void PlayerEntity::damage(const int damage) { Entity::damage(damage); }

    void PlayerEntity::kill() { Entity::kill(); }

    void PlayerEntity::jump()
    {
        if (jump_count < max_jump_count)
        {
            vertical_velocity = jump_force;
            is_grounded = false;
            jump_count++;
        }
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

        const float control_multiplier = is_grounded ? 1.0f : air_control;
        const float speed_multiplier = (sprinting ? sprint_multiplier : walk_speed_multiplier) * control_multiplier;

        float target_speed = 0.0f;

        if (IsKeyDown(controls->movement_right))
            target_speed = walk_speed * speed_multiplier;
        else if (IsKeyDown(controls->movement_left))
            target_speed = -walk_speed * speed_multiplier;
        else if (is_grounded)
            target_speed = 0.0f;
        else
            return;

        if (std::abs(target_speed - horizontal_velocity) > 0.1f)
        {
            const float direction = target_speed > horizontal_velocity ? 1.0f : -1.0f;

            if (const float acc = acceleration * control_multiplier * deltaTime; std::abs(acc) > std::abs(target_speed - horizontal_velocity))
                horizontal_velocity = target_speed;
            else
                horizontal_velocity += acc * direction;
        }
    }

    void PlayerEntity::UpdateCameraCenterSmoothFollow(const float delta) const
    {
        if (!owner)
            return;

        const int background_width = owner->get_background()->width;
        const int background_height = owner->get_background()->height;

        // Background position and scale from PlayableStage::draw
        constexpr Vector2 bg_position = {-1000, -3150};
        constexpr float bg_scale = 2.3f;

        constexpr float minEffectLength = 10;
        owner->camera.offset = (Vector2) {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        const Vector2 diff = Vector2Subtract(position, owner->camera.target);

        // Update camera target with smooth follow
        if (const float length = Vector2Length(diff); length > minEffectLength)
        {
            constexpr float fractionSpeed = 0.9f;
            constexpr float minSpeed = 10;
            const float distanceFactor = length / minEffectLength; // Multiplier based on distance
            const float speed = fmaxf(fractionSpeed * length * distanceFactor, minSpeed);
            owner->camera.target = Vector2Add(owner->camera.target, Vector2Scale(diff, speed * delta / length));
        }

        // Calculate the visible area dimensions
        const float halfScreenWidth = owner->camera.offset.x;
        const float halfScreenHeight = owner->camera.offset.y;

        // Calculate camera bounds based on background size and screen dimensions
        const float minX = bg_position.x + halfScreenWidth;
        const float minY = bg_position.y + halfScreenHeight;
        const float maxX = bg_position.x + (background_width * bg_scale) - halfScreenWidth;
        const float maxY = bg_position.y + (background_height * bg_scale) - halfScreenHeight;

        // Clamp camera target position to stay within bounds
        owner->camera.target.x = Clamp(owner->camera.target.x, minX, maxX);
        owner->camera.target.y = Clamp(owner->camera.target.y, minY, maxY);
    }
} // namespace artifact
