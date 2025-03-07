// title_screen.cpp
#include "../include/stages/title_screen.h"
#include <raylib.h>
#include "game.h"

namespace artifact
{
    void TitleScreen::startup()
    {
        sky_clouds_background_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/sunny-mountains-sky.png"));
        mountain_hills_background_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/sunny-mountains-hills.png"));
        title_image = new Texture2D(LoadTexture("game/texture/menus/title_screen/artifact_logo.png"));

        // Create the vertical container for buttons
        constexpr int button_height = 70;
        const int button_width = GetScreenWidth() / 4;
        constexpr int button_spacing = 10;
        constexpr int container_padding = 10;

        button_container = std::make_unique<VerticalListContainer>("button_container", this, 0, 0, 0, 0);

        button_container->set_gap(button_spacing);
        button_container->set_padding(container_padding);
        button_container->set_background_color(BLANK);

        // Create buttons
        start_button = std::make_unique<ButtonComponent>("start_button", this, 0, 0, button_width, button_height, "Start Game", [] { TraceLog(LOG_INFO, "Start button clicked!"); });

        settings_button = std::make_unique<ButtonComponent>("settings_button", this, 0, 0, button_width, button_height, "Settings Game", [] { TraceLog(LOG_INFO, "Settings button clicked!"); });

        exit_button = std::make_unique<ButtonComponent>("exit_button", this, 0, 0, button_width, button_height, "Exit Game",
                                                        []
                                                        {
                                                            TraceLog(LOG_INFO, "Exit button clicked!");
                                                            Game::get_instance()->exit_game();
                                                        });

        // Configure button appearances
        start_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);
        settings_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);
        exit_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);

        start_button->set_font_size(font_size);
        settings_button->set_font_size(font_size);
        exit_button->set_font_size(font_size);

        // Add buttons to container
        button_container->add_component(start_button.get());
        button_container->add_component(settings_button.get());
        button_container->add_component(exit_button.get());

        button_container->auto_size();
        button_container->set_position((GetScreenWidth() / 2) - (button_container->get_width() / 2), GetScreenHeight() - button_container->get_height() - 20);


        // Play theme music
        menu_music = LoadMusicStream("game/audio/music/mainmenu.WAV");
        menu_music.looping = true;
        PlayMusicStream(menu_music);
    }

    void TitleScreen::draw() const
    {
        ClearBackground(background_color);

        // Draw clouds background layer
        if (sky_clouds_background_image != nullptr)
        {
            const float clouds_scale = calculate_background_scale(sky_clouds_background_image);
            const float scaled_clouds_width = static_cast<float>(sky_clouds_background_image->width) * clouds_scale;
            const int num_clouds = calculate_required_backgrounds(sky_clouds_background_image, clouds_scale);

            for (int i = 0; i < num_clouds; i++)
            {
                draw_texture_scaled(clouds_scale, clouds_scroll + (static_cast<float>(i) * scaled_clouds_width), 0, *sky_clouds_background_image);
            }
        }

        // Draw mountains background layer
        if (mountain_hills_background_image != nullptr)
        {
            const float mountains_scale = calculate_background_scale(mountain_hills_background_image);
            const float scaled_mountains_width = static_cast<float>(mountain_hills_background_image->width) * mountains_scale;
            const int num_mountains = calculate_required_backgrounds(mountain_hills_background_image, mountains_scale);

            for (int i = 0; i < num_mountains; i++)
            {
                draw_texture_scaled(mountains_scale, mountains_scroll + (static_cast<float>(i) * scaled_mountains_width), 0, *mountain_hills_background_image);
            }
        }


        // Draw title
        if (title_image != nullptr)
        {
            const int width = static_cast<int>(static_cast<double>(GetScreenWidth()) / 1.35);
            const int x = (GetScreenWidth() - width) / 2;
            constexpr int y = 0;
            draw_texture_scaled(width, -1, x, y, *title_image);
        }

        // Draw the button container and its contents
        if (button_container)
            button_container->draw();
    }

    void TitleScreen::update() const
    {
        const float dt = GetFrameTime();

        // Update clouds scroll
        if (sky_clouds_background_image != nullptr)
        {
            const float clouds_scale = calculate_background_scale(sky_clouds_background_image);
            const float scaled_clouds_width = static_cast<float>(sky_clouds_background_image->width) * clouds_scale;

            clouds_scroll -= clouds_scroll_speed * dt;
            if (clouds_scroll <= -scaled_clouds_width)
            {
                clouds_scroll = 0.0f;
            }
        }

        // Update mountains scroll
        if (mountain_hills_background_image != nullptr)
        {
            const float mountains_scale = calculate_background_scale(mountain_hills_background_image);
            const float scaled_mountains_width = static_cast<float>(mountain_hills_background_image->width) * mountains_scale;

            mountains_scroll -= mountains_scroll_speed * dt;
            if (mountains_scroll <= -scaled_mountains_width)
            {
                mountains_scroll = 0.0f;
            }
        }


        if (button_container && this->is_menu_in_focus())
            button_container->update(GetMouseX(), GetMouseY());

        // UpdateMusicStream(menu_music);
    }

    void TitleScreen::destroy()
    {
        delete sky_clouds_background_image;
        delete mountain_hills_background_image;
        delete title_image;
        button_container.reset();
        start_button.reset();
        settings_button.reset();
        exit_button.reset();
        UnloadMusicStream(menu_music);
    }

} // namespace artifact
