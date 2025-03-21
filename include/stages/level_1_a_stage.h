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
        void update(float deltaTime) override;
        void destroy() override;
        void startup() override;

    };
} // namespace artifact
