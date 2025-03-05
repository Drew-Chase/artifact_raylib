#include "../include/stages/title_screen.h"
#include <raylib.h>

#include "game.h"

namespace artifact
{
    void TitleScreen::startup()
    {
        background_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/background.png"));

        // Create the start button
        start_button = std::make_unique<ButtonComponent>("start_button",
                                                         GetScreenWidth() / 2 - 100, // Center horizontally
                                                         GetScreenHeight() / 2 - 25, // Center vertically
                                                         200, // Width
                                                         50, // Height
                                                         "Start Game", // Button text
                                                         []
                                                         {
                                                             // Add your game start logic here
                                                             TraceLog(LOG_INFO, "Start button clicked!");
                                                         });
        exit_button = std::make_unique<ButtonComponent>("exit_button",
                                                        GetScreenWidth() / 2 - 100, // Center horizontally
                                                        GetScreenHeight() / 2 - 25 + 60, // Center vertically
                                                        200, // Width
                                                        50, // Height
                                                        "Exit Game", // Button text
                                                        []
                                                        {
                                                            // Add your game start logic here
                                                            TraceLog(LOG_INFO, "Exit button clicked!");
                                                            Game::get_instance()->exit_game();
                                                        });

        // Optionally customize the button colors
        start_button->setColors(DARKBLUE, BLUE, SKYBLUE);
        exit_button->setColors(DARKBLUE, BLUE, SKYBLUE);
    }

    void TitleScreen::draw() const
    {
        if (background_image != nullptr)
            draw_texture_to_fill_rect(GetScreenWidth(), GetScreenHeight(), 0, 0, *background_image);

        // Draw the button
        if (start_button)
            start_button->draw();
        if (exit_button)
            exit_button->draw();
    }

    void TitleScreen::update() const
    {
        // Update the button
        if (start_button)
            start_button->update(GetMouseX(), GetMouseY());
        if (exit_button)
            exit_button->update(GetMouseX(), GetMouseY());
    }

    void TitleScreen::destroy()
    {
        delete background_image;
        start_button.reset();
    }
} // namespace artifact
