#pragma once
#include "entity.h"
#include "sprite_sheet.h"

namespace artifact
{
    class PlayerEntity final : public Entity
    {
        float walk_speed = 300.0f;
        float walk_speed_multiplier = 1;
        float sprint_multiplier = 1.5f;
        bool sprinting = false;

        // Gravity and jumping variables
        float vertical_velocity = 0.0f;
        float horizontal_velocity = 0.0f;
        float gravity = 1800.0f;
        float jump_force = 670.0f;
        bool is_grounded = false;
        int jump_count = 0;
        int max_jump_count = 2;

        // Sprite sheets
        SpriteSheet idle_sheet;


        // Air control and physics constants
        float air_control = 0.8f;
        float ground_friction = 10.0f;
        float air_friction = 1.0f;
        float acceleration = 2000.0f;

        Vector2 bounds{80, 160};

        void handle_input(float deltaTime);
        void apply_gravity(float deltaTime);
        void apply_horizontal_movement(float deltaTime);
        void check_collision();
        void UpdateCameraCenterSmoothFollow(float delta) const;

    public:
        void startup() override;
        void draw() override;
        void update(float deltaTime) override;
        void damage(int damage) override;
        void kill() override;
        void jump();
    };
} // namespace artifact
