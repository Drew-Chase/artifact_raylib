#include "../include/stages/title_screen.h"
#include <fmt/format.h>
#include <raylib.h>


namespace artifact
{
    size_t frames_drawn = 0;
    void TitleScreen::draw() const
    {
        if (background_image != nullptr)
            draw_texture_to_fill_rect(GetScreenWidth(), GetScreenHeight(), 0, 0, *background_image);
        DrawText(fmt::format("Frames Drawn: {}", frames_drawn).c_str(), 20, 100, 24, WHITE);
    }
    void TitleScreen::update() const { frames_drawn++; }
    void TitleScreen::startup() { background_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/background.png")); }
    void TitleScreen::destroy() { delete background_image; }
} // namespace artifact
