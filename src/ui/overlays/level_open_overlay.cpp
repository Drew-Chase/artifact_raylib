
#include "ui/overlays/level_open_overlay.h"
#include "game_utilities.h"

namespace artifact
{
    LevelOpenOverlay::LevelOpenOverlay(Stage *owner, const float duration) : ComponentBase("level_open_overlay", owner) { this->duration = duration; }
    void LevelOpenOverlay::draw() { ComponentBase::draw(); }
    void LevelOpenOverlay::update(const float delta_time)
    {
        ComponentBase::update(delta_time);
        last_frame = GameUtilities::ConvertSecondsToFrames(this->duration, delta_time);
    }
    void LevelOpenOverlay::reset() { current_frame = 0; }
    void LevelOpenOverlay::stop()
    {
        playing = false;
        reset();
    }
    void LevelOpenOverlay::pause() { playing = false; }
    void LevelOpenOverlay::play() { playing = true; }
    bool LevelOpenOverlay::is_playing() const { return playing; }
} // namespace artifact
