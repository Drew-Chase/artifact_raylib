#include "entities/player_entity.h"
#include <cmath>
#include <fmt/format.h>
#include <raymath.h>

#include "direction.h"
#include "entities/enemy_entity.h"
#include "game.h"
#include "game_utilities.h"
#include "stages/playable_stage.h"

namespace artifact
{
    void PlayerEntity::startup()
    {
        Entity::startup();
        max_health = health = 4;
        owner->camera.target = this->position;
        owner->camera.rotation = 0;
        width = height = 64;

        // Load sprite sheets
        idle_sheet = new SpriteSheet("game/texture/entities/player/idle%d.png", 9, 8);
        run_sheet = new SpriteSheet("game/texture/entities/player/run%d.png", 8, 13);
        jump_sheet = new SpriteSheet("game/texture/entities/player/jump_%d.png", 5, 8);
        light_attack_sheet = new SpriteSheet("game/texture/entities/player/AttackB%d.png", 5, 8);
        dash_attack_sheet = new SpriteSheet("game/texture/entities/player/AttackA%d.png", 7, 8);
        hurt_sheet = new SpriteSheet("game/texture/entities/player/hit%d.png", 3, 8);
        death_sheet = new SpriteSheet("game/texture/entities/player/death%d.png", 5, 8);

        // Pause animations by default
        hurt_sheet->pause();
        death_sheet->pause();
        dash_attack_sheet->pause();
        light_attack_sheet->pause();


        // Load SFX
        sfx_jump = LoadSound("game/audio/sfx/playerjump.ogg");
        sfx_hit = LoadSound("game/audio/sfx/playerattack.ogg");
        sfx_dash = LoadSound("game/audio/sfx/playercharge.ogg");

        // Load interface sprites
        heart_texture = LoadTexture("game/texture/ui/heart.png");
        life_texture = LoadTexture("game/texture/ui/life.png");
        coin_texture = LoadTexture("game/texture/ui/coin.png");

        // Set up the entity collision callback
        if (collider)
        {
            collider = std::make_unique<Collider>(position.x, position.y, width, height, [this](Entity *entity)
                                                  { this->on_entity_collision(entity); });
            collider->set_owner(this);
        }
    }
    void PlayerEntity::draw()
    {
        Entity::draw();
        if (Game::get_instance()->debug_mode)
        {
            const std::string lines[] =
                    {
                            fmt::format("FPS: {} ({:.1f}ms)", GetFPS(), GetFrameTime() * 1000),
                            fmt::format("Grounded: {}, VVel: {:.1f}, HVel: {:.1f}", is_grounded ? "true" : "false", vertical_velocity, horizontal_velocity),
                            fmt::format("Player Pos: X: {:.1f}, Y: {:.1f}", this->position.x, this->position.y),
                            fmt::format("Dash: {}, Light: {}, Inv: {}, Death: {}", dash_attack_frames, light_attack_frames, invincibility_frames, death_frames),
                            fmt::format("Jump Count: {}/{}", jump_count, max_jump_count),
                    };

            constexpr unsigned short font_size = 16;

            unsigned int text_width = 0;
            for (const auto &line: lines)
            {
                if (const unsigned int height = MeasureText(line.c_str(), font_size); height > text_width)
                    text_width = height;
            }


            constexpr int line_height = font_size + 2;
            constexpr int total_height = line_height * std::size(lines);
            DrawRectangleRec({this->position.x - 10, this->position.y - total_height - 20, static_cast<float>(text_width + 20), static_cast<float>(total_height + 10)}, ColorAlpha(BLACK, .5f));

            for (size_t i = 0; i < std::size(lines); i++)
            {
                DrawText(lines[i].c_str(), this->position.x, this->position.y - total_height - 10 + i * line_height, font_size, WHITE);
            }
        }
        const Vector2 sprite_position_flipped = {position.x - 32, position.y};
        const Vector2 sprite_position = {position.x + 16, position.y};
        constexpr float sprite_scale = 2.2f;

        // Draw animations
        if (Entity::is_dead())
        {
            death_sheet->draw(sprite_position, sprite_scale);
        } else if (hurt_frames > 0)
        {
            if (hurt_sheet->is_flipped())
                hurt_sheet->draw(sprite_position_flipped, sprite_scale);
            else
                hurt_sheet->draw(sprite_position, sprite_scale);
        } else if (light_attack_frames > 0)
        {
            if (light_attack_sheet->is_flipped())
                light_attack_sheet->draw(sprite_position_flipped, sprite_scale);
            else
                light_attack_sheet->draw(sprite_position, sprite_scale);
        } else if (dash_attack_frames > 0)
        {
            if (dash_attack_sheet->is_flipped())
                dash_attack_sheet->draw(sprite_position_flipped, sprite_scale);
            else
                dash_attack_sheet->draw(sprite_position, sprite_scale);
        } else if (is_grounded)
        {
            if (horizontal_velocity == 0)
            {
                if (idle_sheet->is_flipped())
                    idle_sheet->draw(sprite_position_flipped, sprite_scale);
                else
                    idle_sheet->draw(sprite_position, sprite_scale);
            } else
            {
                if (run_sheet->is_flipped())
                    run_sheet->draw(sprite_position_flipped, sprite_scale);
                else
                    run_sheet->draw(sprite_position, sprite_scale);
            }
        } else
        {
            if (jump_sheet->is_flipped())
                jump_sheet->draw(sprite_position_flipped, sprite_scale);
            else
                jump_sheet->draw(sprite_position, sprite_scale);
        }
    }
    void PlayerEntity::draw_stats() const
    {
        float x = 10;
        float y = 10;
        constexpr int gap = 10;
        float scale = 0.2f;
        for (int i = 0; i < health; i++)
        {
            DrawTextureEx(heart_texture, Vector2{x, y}, 0, scale, WHITE);
            x += heart_texture.width * scale + gap;
        }
        x = 10;
        y += heart_texture.height * scale + gap;
        scale = 0.2f;
        for (int i = 0; i < lives; i++)
        {
            DrawTextureEx(life_texture, Vector2{x, y}, 0, scale, WHITE);
            x += life_texture.width * scale + gap;
        }
    }
    void PlayerEntity::update(const float delta_time)
    {
        if (!IsWindowReady() || is_being_destroyed)
            return;
        Entity::update(delta_time);
        owner->camera.zoom = 1.5f * fminf(GetScreenWidth() / 1920.0f, GetScreenHeight() / 1080.0f);

        if (Entity::is_dead())
        {
            if (death_frames > 0)
            {
                death_frames--;
                if (death_sheet->get_current_frame() < death_sheet->get_frame_count() - 1 && death_sheet)
                    death_sheet->update(delta_time);
            }
            return;
        }
        if (is_teleporting)
            this->horizontal_velocity = 0;

        handle_input(delta_time);
        apply_horizontal_movement(delta_time);
        check_collision();
        apply_gravity(delta_time);


        if (this->invincibility_frames > 0)
            this->invincibility_frames--;
        if (this->hurt_frames > 0)
            this->hurt_frames--;
        if (light_attack_sheet)
        {
            if (light_attack_frames > 0)
                light_attack_frames--;
            else
                light_attack_sheet->set_frame(0);
        }
        if (dash_attack_sheet)
        {
            if (dash_attack_frames > 0)
                dash_attack_frames--;
            else
                dash_attack_sheet->set_frame(0);
        }

        if (idle_sheet)
        {
            idle_sheet->update(delta_time);
            idle_sheet->set_pulse(is_teleporting);
        }
        if (run_sheet)
        {
            if (sprinting)
                run_sheet->set_framerate(13);
            else
                run_sheet->set_framerate(8);
            run_sheet->update(delta_time);
        }
        if (jump_sheet)
            jump_sheet->update(delta_time);
        if (light_attack_sheet)
            light_attack_sheet->update(delta_time);
        if (dash_attack_sheet)
            dash_attack_sheet->update(delta_time);
        if (hurt_sheet)
            hurt_sheet->update(delta_time);

        update_camera_center_smooth_follow(delta_time);
    }
    void PlayerEntity::damage(const int damage, const Direction direction)
    {
        if (dash_attack_frames > 0 || light_attack_frames > 0 || invincibility_frames > 0 || is_dead())
            return;

        if (health - damage <= 0) // Should be dead.
        {
            death_sheet->play();
            death_frames = GameUtilities::ConvertSecondsToFrames(2, GetFrameTime());
        }
        invincibility_frames = GameUtilities::ConvertSecondsToFrames(1, GetFrameTime());
        hurt_frames = GameUtilities::ConvertSecondsToFrames(0.25, GetFrameTime());

        Entity::damage(damage, direction);

        if (!is_dead())
        {
            hurt_sheet->play_once();
            if (direction == Direction::RIGHT)
            {
                horizontal_velocity = 300;
                vertical_velocity = 300;
                is_grounded = false;
            } else
            {
                horizontal_velocity = -300;
                vertical_velocity = 300;
                is_grounded = false;
            }
        }
    }
    void PlayerEntity::kill()
    {
        if (is_dead())
            return;
        Entity::kill();
        death_sheet->play();
        death_sheet->play_once(true);
    }
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
    void PlayerEntity::handle_input(const float delta_time)
    {
        const ControlsSettings *controls = Game::get_instance()->controls_settings;

#ifdef DEBUG
        if (ControlsSettings::pressed(KEY_B))
            Game::get_instance()->debug_mode = !Game::get_instance()->debug_mode;
        if (Game::get_instance()->debug_mode)
        {
            const int fps = GetFPS();
            if (IsKeyDown(KEY_UP))
                SetTargetFPS(fps + 10);
            if (IsKeyDown(KEY_DOWN))
                SetTargetFPS(fps - 10);
        }

        if (is_teleporting)
            return;

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
            hurt_sheet->set_flipped(false);

        } else if (ControlsSettings::down(controls->movement_left))
        {
            target_speed = -walk_speed * speed_multiplier;
            idle_sheet->set_flipped(true);
            run_sheet->set_flipped(true);
            jump_sheet->set_flipped(true);
            dash_attack_sheet->set_flipped(true);
            light_attack_sheet->set_flipped(true);
            hurt_sheet->set_flipped(true);
        } else if (is_grounded)
            target_speed = 0.0f;

        if (std::abs(target_speed - horizontal_velocity) > 0.1f)
        {
            const float direction = target_speed > horizontal_velocity ? 1.0f : -1.0f;

            if (const float acc = acceleration * control_multiplier * delta_time; std::abs(acc) > std::abs(target_speed - horizontal_velocity))
                horizontal_velocity = target_speed;
            else
                horizontal_velocity += acc * direction;
        }

        if (ControlsSettings::pressed(controls->combat_dash))
        {
            if (dash_attack_frames > 0 || light_attack_frames > 0)
                return;
            dash_attack_frames = GameUtilities::ConvertSecondsToFrames(1, delta_time);
            dash_attack_sheet->play_once();
            constexpr int dash_momentum = 1000;
            if (dash_attack_sheet->is_flipped())
                horizontal_velocity = -dash_momentum;
            else
                horizontal_velocity = dash_momentum;
            vertical_velocity += 200;
            is_grounded = false;
            PlaySound(sfx_dash);
        } else if (ControlsSettings::pressed(controls->combat_light))
        {
            if (dash_attack_frames > 0 || light_attack_frames > 0)
                return;
            light_attack_frames = GameUtilities::ConvertSecondsToFrames(.75, delta_time);
            light_attack_sheet->play_once();
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

        // Calculate the visible area dimensions, factoring in zoom
        const float halfScreenWidth = owner->camera.offset.x / owner->camera.zoom;
        const float halfScreenHeight = owner->camera.offset.y / owner->camera.zoom;

        // Calculate camera bounds based on background size, screen dimensions, and zoom
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
    void PlayerEntity::on_entity_collision(Entity *entity)
    {
        if (entity == nullptr)
            return;

        // Check if the entity is an enemy
        if (auto *enemy = dynamic_cast<EnemyEntity *>(entity))
        {
            const Direction direction = enemy->get_position().x > position.x ? Direction::RIGHT : Direction::LEFT;
            if (dash_attack_frames > 0 || light_attack_frames > 0)
                enemy->damage(attack_damage, direction);
        }
    }
    bool PlayerEntity::check_is_on_ground() const
    {
        if (!owner || owner->destroyed())
            return false;

        struct CheckPoint
        {
            float x_percent; // Percentage of width
            float y_percent; // Percentage of height
        };

        const std::vector<CheckPoint> check_points = {
                // Bottom edge points (for ground detection)
                {0.3f, 1.0f},
                {0.5f, 1.0f},
                {0.8f, 1.0f},
        };

        for (const auto &[x_percent, y_percent]: check_points)
        {
            const int check_x = static_cast<int>(position.x + bounds.x * x_percent);
            const int check_y = static_cast<int>(position.y + bounds.y * y_percent);

            std::vector<Collider> nearby_colliders = owner->get_colliders_closest_to(check_x, check_y, false);

            if (nearby_colliders.empty())
                continue;

            for (const Collider &collider: nearby_colliders)
            {
                if (!CheckCollisionPointRec({static_cast<float>(check_x), static_cast<float>(check_y)}, collider.bounds))
                    continue;
                if (!collider.is_blocking)
                    continue;
                if (vertical_velocity <= 0)
                {
                    return true;
                }
            }
        }

        return false;
    }
    void PlayerEntity::apply_gravity(const float delta_time)
    {
        if (!is_grounded)
        {
            vertical_velocity -= gravity * delta_time;
            position.y -= vertical_velocity * delta_time;
        }
    }
    void PlayerEntity::apply_horizontal_movement(const float delta_time)
    {
        position.x += horizontal_velocity * delta_time;

        const float friction = is_grounded ? ground_friction : air_friction;

        if (std::abs(horizontal_velocity) > 0.1f)
        {

            if (const float slowdown = friction * delta_time * std::copysign(1.0f, horizontal_velocity); std::abs(slowdown) > std::abs(horizontal_velocity))
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
        if (!owner || owner->destroyed())
            return;
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

        const std::vector<CheckPoint> check_points = {
                // Bottom edge points (for ground detection)
                {0.1f, 1.0f, BOTTOM},
                {0.5f, 1.0f, BOTTOM},
                {0.9f, 1.0f, BOTTOM},

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

        bool is_colliding_bottom = false;
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
                    case LEFT:
                        if (horizontal_velocity < 0)
                        {
                            position.x = collider.bounds.x + collider.bounds.width - 1;
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
                        if (vertical_velocity != 0)
                        {
                            position.y = collider.bounds.y + collider.bounds.height + 1;
                            vertical_velocity = 0;
                        }
                        break;

                    case BOTTOM:
                        if (vertical_velocity <= 0)
                        {
                            if (collider.bounds.y > highest_ground)
                            {
                                highest_ground = collider.bounds.y;
                            }
                            is_colliding_bottom = true;
                        }
                        break;
                }

                break;
            }
        }

        if (check_is_on_ground())
        {
            is_grounded = true;
            jump_count = 0;
            position.y = highest_ground - bounds.y; // Teleports the player up-words
            vertical_velocity = 0;
        } else if (is_colliding_bottom)
        {
            is_grounded = true;
        }
    }
    bool PlayerEntity::is_facing_right() const { return idle_sheet->is_flipped(); }
    void PlayerEntity::respawn(const bool should_remove_life)
    {
        if (lives <= 0)
        {
            destroy();
            Game::get_instance()->get_stage_manager()->load_stage(Stages::TITLE_SCREEN);
        } else
        {
            if (should_remove_life)
                lives--;
            health = max_health;
            owner->spawn_entities();

            const auto [x, y] = owner->get_spawn_position();
            set_position(x, y);
        }
    }
    void PlayerEntity::destroy()
    {
        Entity::destroy();
        // unload sprite sheet
        delete death_sheet;
        death_sheet = nullptr;
        delete hurt_sheet;
        hurt_sheet = nullptr;
        delete idle_sheet;
        idle_sheet = nullptr;
        delete run_sheet;
        run_sheet = nullptr;
        delete jump_sheet;
        jump_sheet = nullptr;
        delete dash_attack_sheet;
        dash_attack_sheet = nullptr;
        delete light_attack_sheet;
        light_attack_sheet = nullptr;
    }
    bool PlayerEntity::is_dead() const
    {
        return Entity::is_dead() && death_frames == 0;
    }
    void PlayerEntity::set_position(const float x, const float y)
    {
        invincibility_frames = 0;
        hurt_frames = 0;
        dash_attack_frames = 0;
        light_attack_frames = 0;
        dash_attack_sheet->reset();
        light_attack_sheet->reset();
        horizontal_velocity = 0;
        vertical_velocity = 0;

        death_sheet->reset();
        owner->level_open_overlay->restart();

        owner->camera.target = {x, y};
        Entity::set_position(x, y);
    }
    void PlayerEntity::set_teleporting(const bool is_teleporting)
    {
        this->is_teleporting = is_teleporting;
    }
} // namespace artifact
