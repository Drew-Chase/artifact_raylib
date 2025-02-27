
#include "../include/stages/title_screen.h"

#include <raylib.h>

#include "game.h"

namespace artifact
{
    size_t frames_drawn = 0;
    void TitleScreen::draw() const
    {
        DrawText(fmt::format("Frames Drawn: {}", frames_drawn).c_str(), 20, 100, 24, WHITE);
        frames_drawn++;
    }
} // namespace artifact
