
#include "../include/stages/title_screen.h"

#include <raylib.h>

#include "game.h"

namespace artifact
{
    size_t frames_drawn = 0;
    void TitleScreen::draw() const
    {
        DrawText(fmt::format("Frames Drawn: {}", frames_drawn).c_str(), 20, 100, 24, WHITE);
        draw_texture_to_fill_rect(GetScreenWidth(), GetScreenHeight(), 0, 0, background_image);
    }
    void TitleScreen::update() const { frames_drawn++; }
    void TitleScreen::startup()
    {
        background_image = LoadTexture("game/texture/menus/title_screen/background.png");

    }
} // namespace artifact
