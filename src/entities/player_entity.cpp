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
        owner->camera.rotation = 0;

        // Load sprite sheets
        idle_sheet = new SpriteSheet("game/texture/entities/player/idle%d.png", 9, 8);
        run_sheet = new SpriteSheet("game/texture/entities/player/run%d.png", 8, 13);
        jump_sheet = new SpriteSheet("game/texture/entities/player/jump_%d.png", 5, 8);
        light_attack_sheet = new SpriteSheet("game/texture/entities/player/AttackB%d.png", 5, 8);
        dash_attack_sheet = new SpriteSheet("game/texture/entities/player/AttackA%d.png", 7, 8);

        // Load SFX
        sfx_jump = LoadSound("game/audio/sfx/playerjump.ogg");
        sfx_hit = LoadSound("game/audio/sfx/playerattack.ogg");
        sfx_dash = LoadSound("game/audio/sfx/playercharge.ogg");
    }

    void PlayerEntity::draw()
    {
        Entity::draw();
        if (Game::get_instance()->debug_mode)
        {
            const std::string grounded_text = fmt::format("Grounded: {}, VVel: {:.1f}, HVel: {:.1f}", is_grounded ? "true" : "false", vertical_velocity, horizontal_velocity);
            const std::string position_text = fmt::format("Player Pos: X: {:.1f}, Y: {:.1f}", this->position.x, this->position.y);
            const std::string attacks_text = fmt::format("Dash: {}, Light: {}", dash_attack_frames, light_attack_frames);

            const int text_width = std::max({MeasureText(grounded_text.c_str(), 16), MeasureText(position_text.c_str(), 16), MeasureText(attacks_text.c_str(), 16)});

            DrawRectangleRec({this->position.x - 10, this->position.y - 100, static_cast<float>(text_width + 20), 82}, ColorAlpha(BLACK, .5f));
            DrawRectangleLinesEx({position.x, position.y, bounds.x, bounds.y}, 1, BLUE);
            DrawText(grounded_text.c_str(), this->position.x, this->position.y - 90, 16, WHITE);
            DrawText(position_text.c_str(), this->position.x, this->position.y - 64, 16, WHITE);
            DrawText(attacks_text.c_str(), this->position.x, this->position.y - 42, 16, WHITE);
        }

        // Draw animations
        if (light_attack_frames > 0)
        {
            if (light_attack_sheet->is_flipped())
                light_attack_sheet->draw(Vector2{position.x - 32, position.y}, 2.2);
            else
                light_attack_sheet->draw(Vector2{position.x + 16, position.y}, 2.2);
        } else if (dash_attack_frames > 0)
        {
            if (dash_attack_sheet->is_flipped())
                dash_attack_sheet->draw(Vector2{position.x - 32, position.y}, 2.2);
            else
                dash_attack_sheet->draw(Vector2{position.x + 16, position.y}, 2.2);
        } else if (is_grounded)
        {
            if (horizontal_velocity == 0)
            {
                if (idle_sheet->is_flipped())
                    idle_sheet->draw(Vector2{position.x - 32, position.y}, 2.2);
                else
                    idle_sheet->draw(Vector2{position.x + 16, position.y}, 2.2);
            } else
            {
                if (run_sheet->is_flipped())
                    run_sheet->draw(Vector2{position.x - 32, position.y}, 2.2);
                else
                    run_sheet->draw(Vector2{position.x + 16, position.y}, 2.2);
            }
        } else
        {
            if (jump_sheet->is_flipped())
                jump_sheet->draw(Vector2{position.x - 32, position.y}, 2.2);
            else
                jump_sheet->draw(Vector2{position.x + 16, position.y}, 2.2);
        }
    }

    void PlayerEntity::update(const float deltaTime)
    {
        if (!IsWindowReady())
            return;
        Entity::update(deltaTime);

        owner->camera.zoom = 1.5f * fminf(GetScreenWidth() / 1920.0f, GetScreenHeight() / 1080.0f);

        handle_input(deltaTime);
        check_collision();
        apply_gravity(deltaTime);
        apply_horizontal_movement(deltaTime);

        if (light_attack_frames > 0)
            light_attack_frames--;
        else
            light_attack_sheet->set_frame(0);
        if (dash_attack_frames > 0)
            dash_attack_frames--;
        else
            dash_attack_sheet->set_frame(0);


        idle_sheet->update(deltaTime);
        if (sprinting)
            run_sheet->set_framerate(13);
        else
            run_sheet->set_framerate(8);
        run_sheet->update(deltaTime);
        jump_sheet->update(deltaTime);
        light_attack_sheet->update(deltaTime);
        dash_attack_sheet->update(deltaTime);

        update_camera_center_smooth_follow(deltaTime);
    }

    void PlayerEntity::apply_gravity(const float deltaTime)
    {
        if (!is_grounded)
        {
            vertical_velocity -= gravity * deltaTime;
            position.y -= vertical_velocity * deltaTime;
        }
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
            // TODO: Add landing effects
        }
    }

    void PlayerEntity::damage(const int damage) { Entity::damage(damage); }

    void PlayerEntity::kill() { Entity::kill(); }

    void PlayerEntity::jump()
    {
        if (jump_count < max_jump_count)
        {
            PlaySound(sfx_jump);
            vertical_velocity = jump_force;
            is_grounded = false;
            jump_count++;
        }
    }


    void PlayerEntity::handle_input(const float deltaTime)
    {
        const ControlsSettings *controls = Game::get_instance()->controls_settings;

#ifdef DEBUG
        if (ControlsSettings::pressed(KEY_B))
            Game::get_instance()->debug_mode = !Game::get_instance()->debug_mode;
#endif
        if (ControlsSettings::down(controls->movement_sprint))
            sprinting = controls->toggle_sprint ? !sprinting : true;
        else if (ControlsSettings::up(controls->movement_sprint) && !controls->toggle_sprint)
            sprinting = false;

        if (ControlsSettings::pressed(controls->movement_jump))
            jump();

        const float control_multiplier = is_grounded ? 1.0f : air_control;
        const float speed_multiplier = (sprinting ? sprint_multiplier : walk_speed_multiplier) * control_multiplier;

        float target_speed = 0.0f;

        if (ControlsSettings::down(controls->movement_right))
        {
            target_speed = walk_speed * speed_multiplier;
            idle_sheet->set_flipped(false);
            run_sheet->set_flipped(false);
            jump_sheet->set_flipped(false);
            dash_attack_sheet->set_flipped(false);
            light_attack_sheet->set_flipped(false);

        } else if (ControlsSettings::down(controls->movement_left))
        {
            target_speed = -walk_speed * speed_multiplier;
            idle_sheet->set_flipped(true);
            run_sheet->set_flipped(true);
            jump_sheet->set_flipped(true);
            dash_attack_sheet->set_flipped(true);
            light_attack_sheet->set_flipped(true);
        } else if (is_grounded)
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

        if (ControlsSettings::pressed(controls->combat_dash))
        {
            if (dash_attack_frames > 0 || light_attack_frames > 0)
                return;
            dash_attack_frames = 60 * (GetFPS() / 60);
            constexpr int dash_momentum = 1000;
            if (dash_attack_sheet->is_flipped())
                horizontal_velocity = -dash_momentum;
            else
                horizontal_velocity = dash_momentum;
            vertical_velocity += 200;
            PlaySound(sfx_dash);
        } else if (ControlsSettings::pressed(controls->combat_light))
        {
            if (dash_attack_frames > 0 || light_attack_frames > 0)
                return;
            light_attack_frames = 30 * (GetFPS() / 60);
            PlaySound(sfx_hit);
        }
    }

    void PlayerEntity::update_camera_center_smooth_follow(const float delta) const
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
    void PlayerEntity::add_momentum(const float x, const float y)
    {
        horizontal_velocity += x;
        vertical_velocity += y;
    }
} // namespace artifact
