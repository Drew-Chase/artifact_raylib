#pragma once
#include "ui/components/component_base.h"

namespace artifact
{
    class LevelOpenOverlay final : public ComponentBase
    {

        Vector2 left{0,0};
        Vector2 right{0,0};
        Vector2 top{0,0};
        Vector2 bottom{0,0};
        Rectangle rect;
        // the animation duration in seconds.
        float duration = 2;
        bool playing = true;
        size_t current_frame = 0;
        size_t last_frame = 0;

    public:
        explicit LevelOpenOverlay(Stage *owner, float duration);
        void draw() override;
        void update(float delta_time) override;
        bool is_playing() const;
        void play();
        void stop();
        void pause();
        void reset();
        void restart();
    };
} // namespace artifact
