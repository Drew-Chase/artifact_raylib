#pragma once
#include "ui/components/component_base.h"

namespace artifact
{
    class LevelOpenOverlay final : public ComponentBase
    {

        Rectangle left{};
        Rectangle right{};
        Rectangle top{};
        Rectangle bottom{};
        // the animation duration in seconds.
        float duration = 2;
        bool playing = false;
        size_t current_frame = 0;
        size_t last_frame = 0;

    public:
        explicit LevelOpenOverlay(Stage *owner, float duration);
        void draw() override;
        void update(float deltaTime) override;
        bool is_playing() const;
        void play();
        void stop();
        void pause();
        void reset();
    };
} // namespace artifact
