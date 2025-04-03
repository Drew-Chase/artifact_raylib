
#include "ui/overlays/level_open_overlay.h"
#include "game_utilities.h"

namespace artifact
{
    LevelOpenOverlay::LevelOpenOverlay(Stage *owner, const float duration) : ComponentBase("level_open_overlay", owner) { this->duration = duration; }
    void LevelOpenOverlay::draw() { ComponentBase::draw(); }
    void LevelOpenOverlay::update(const float deltaTime)
    {
        ComponentBase::update(deltaTime);
        last_frame = GameUtilities::ConvertSecondsToFrames(this->duration, deltaTime);
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
