#pragma once
#include "playable_stage.h"

namespace artifact
{
    class Level1AStage final : public PlayableStage
    {
        Music music{};
    public:
        explicit Level1AStage();
        void draw() const override;
        void update(float delta_time) override;
        void destroy() override;
        void startup() override;
        Vector2 get_spawn_position() const override;
    };
} // namespace artifact
