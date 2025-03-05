// title_screen.cpp
#include "../include/stages/title_screen.h"
#include <raylib.h>
#include "game.h"

namespace artifact
{
    void TitleScreen::startup()
    {
        background_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/sunny-mountains-sky.png"));
        title_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/artifact_logo.png"));

        // Create the vertical container for buttons
        constexpr int button_width = 200;
        constexpr int button_height = 50;
        constexpr int button_spacing = 10;
        constexpr int container_width = button_width;
        constexpr int container_padding = 10;
        constexpr int container_height = button_height * 2 + button_spacing + container_padding * 2;

        // Position the container in the center of the screen
        const int container_x = (GetScreenWidth() - container_width) / 2;
        const int container_y = GetScreenHeight() * 0.6f; // Position at 60% of screen height

        button_container = std::make_unique<VerticalListContainer>("button_container", container_x, container_y, container_width, container_height);

        button_container->set_gap(button_spacing);
        button_container->set_padding(container_padding);
        button_container->set_background_color(ColorAlpha(RED, .2));

        // Create buttons
        start_button = std::make_unique<ButtonComponent>("start_button", container_x, container_y, button_width, button_height, "Start Game", [] { TraceLog(LOG_INFO, "Start button clicked!"); });

        exit_button = std::make_unique<ButtonComponent>("exit_button", container_x, container_y + button_height + button_spacing, button_width, button_height, "Exit Game",
                                                        []
                                                        {
                                                            TraceLog(LOG_INFO, "Exit button clicked!");
                                                            Game::get_instance()->exit_game();
                                                        });

        // Configure button appearances
        start_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);
        exit_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);

        start_button->set_font_size(24);
        exit_button->set_font_size(24);

        // Add buttons to container
        button_container->add_component(start_button.get());
        button_container->add_component(exit_button.get());
    }

    void TitleScreen::draw() const
    {
        ClearBackground(background_color);

        // Draw background
        if (background_image != nullptr)
            draw_texture_to_fill_rect(GetScreenWidth(), GetScreenHeight(), 0, 0, *background_image);

        // Draw title
        if (title_image != nullptr)
        {
            const int width = GetScreenWidth() / 2;
            const int height = GetScreenHeight() / 2;
            const int x = (GetScreenWidth() - width) / 2;
            const int y = 20;
            draw_texture_scaled(width, height, x, y, *title_image);
        }

        // Draw the button container and its contents
        if (button_container)
            button_container->draw();
    }

    void TitleScreen::update() const
    {
        if (button_container)
            button_container->update(GetMouseX(), GetMouseY());
    }

    void TitleScreen::destroy()
    {
        delete background_image;
        delete title_image;
        button_container.reset();
        start_button.reset();
        exit_button.reset();
    }
} // namespace artifact
