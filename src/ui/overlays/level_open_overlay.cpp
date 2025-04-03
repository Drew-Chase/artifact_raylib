#include "ui/overlays/level_open_overlay.h"
#include "game_utilities.h"

namespace artifact
{
    LevelOpenOverlay::LevelOpenOverlay(Stage *owner, const float duration) : ComponentBase("level_open_overlay", owner)
    {
        this->duration = duration;
        const float width = GetScreenWidth();
        const float height = GetScreenHeight();
        rect = {0, 0, width, height};

        // Initialize positions to cover the screen
        left = {0, 0};
        right = {0, 0};
        top = {0, 0};
        bottom = {0, 0};
    }
    void LevelOpenOverlay::draw()
    {
        if (!is_playing())
            return;

        const float width = GetScreenWidth();
        const float height = GetScreenHeight();

        // Draw four rectangles from the center moving to each corner
        DrawRectanglePro({left.x, left.y, width / 2, height}, {0, 0}, 0, BLACK);
        DrawRectanglePro({right.x, right.y, width / 2, height}, {0, 0}, 0, BLACK);
        DrawRectanglePro({0, top.y, width, height / 2}, {0, 0}, 0, BLACK);
        DrawRectanglePro({0, bottom.y, width, height / 2}, {0, 0}, 0, BLACK);
    }
    void LevelOpenOverlay::update(const float delta_time)
    {
        if (!is_playing())
            return;

        last_frame = GameUtilities::ConvertSecondsToFrames(this->duration, GetFrameTime());
        if (last_frame == 0)
            return;

        if (current_frame >= last_frame)
        {
            stop();
            return;
        }

        const float percentage = static_cast<float>(current_frame) / last_frame;
        const float screenWidth = GetScreenWidth();
        const float screenHeight = GetScreenHeight();

        // Move rectangles from center to corners
        // Left rectangle moves left
        left.x = -percentage * screenWidth / 2;

        // Right rectangle moves right
        right.x = screenWidth / 2 + percentage * screenWidth / 2;

        // Top rectangle moves up
        top.y = -percentage * screenHeight / 2;

        // Bottom rectangle moves down
        bottom.y = screenHeight / 2 + percentage * screenHeight / 2;

        current_frame++;
    }
    void LevelOpenOverlay::reset() { current_frame = 0; }
    void LevelOpenOverlay::restart()
    {
        reset();
        play();
    }
    void LevelOpenOverlay::stop()
    {
        playing = false;
        reset();
    }
    void LevelOpenOverlay::pause() { playing = false; }
    void LevelOpenOverlay::play() { playing = true; }
    bool LevelOpenOverlay::is_playing() const { return playing; }
} // namespace artifact
