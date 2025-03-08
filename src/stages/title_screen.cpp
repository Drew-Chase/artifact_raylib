// title_screen.cpp
#include "../include/stages/title_screen.h"
#include <raylib.h>
#include "game.h"

namespace artifact
{
    void TitleScreen::startup()
    {
        owner->push_to_zindex(this);
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

        settings_button = std::make_unique<ButtonComponent>("settings_button", this, 0, 0, button_width, button_height, "Settings Game",
                                                            [this]
                                                            {
                                                                TraceLog(LOG_INFO, "Settings button clicked!");
                                                                settings_screen = new SettingsScreen(this);
                                                            });

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

        // Play theme music
        menu_music = LoadMusicStream("game/audio/music/mainmenu.wav");
        menu_music.looping = true;
        PlayMusicStream(menu_music);
    }
    void TitleScreen::draw() const
    {
        ClearBackground(BLACK);
        draw_background();

        if (settings_screen != nullptr)
        {
            settings_screen->draw();
        } else
        {
            // Draw title
            if (title_image != nullptr)
            {
                int width = -1;
                int height = static_cast<int>(static_cast<double>(GetScreenHeight()) / 1.5);
                scale_texture(width, height, *title_image);

                constexpr int y = 0;
                const int x = (GetScreenWidth() - width) / 2;
                draw_texture_scaled(width, height, x, y, *title_image);
            }

            // Draw the button container and its contents
            if (button_container)
                button_container->draw();
        }
    }
    void TitleScreen::update(const float deltaTime) const
    {
        UpdateMusicStream(menu_music);
        update_background(deltaTime);

        if (settings_screen != nullptr)
        {
            settings_screen->update(GetMouseX(), GetMouseY());
        } else
        {
            if (button_container && this->is_menu_in_focus())
                button_container->update(GetMouseX(), GetMouseY());
            button_container->set_position(GetScreenWidth() / 2 - button_container->get_width() / 2, GetScreenHeight() - button_container->get_height() - 20);
        }
    }
    void TitleScreen::draw_background() const
    {
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
    }
    void TitleScreen::update_background(const float deltaTime) const
    {

        // Update clouds scroll
        if (sky_clouds_background_image != nullptr)
        {
            const float clouds_scale = calculate_background_scale(sky_clouds_background_image);
            const float scaled_clouds_width = static_cast<float>(sky_clouds_background_image->width) * clouds_scale;

            clouds_scroll -= clouds_scroll_speed * deltaTime;
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

            mountains_scroll -= mountains_scroll_speed * deltaTime;
            if (mountains_scroll <= -scaled_mountains_width)
            {
                mountains_scroll = 0.0f;
            }
        }
    }
    void TitleScreen::destroy()
    {
        // Free dynamically allocated resources
        delete sky_clouds_background_image;
        delete mountain_hills_background_image;
        delete title_image;
        delete settings_screen;

        // Set pointers to null to avoid dangling pointers
        mountain_hills_background_image = nullptr;
        title_image = nullptr;
        sky_clouds_background_image = nullptr;
        settings_screen = nullptr;

        // Reset unique pointers for UI components
        button_container->destroy();
        button_container.reset();

        // Remove this menu stage from z-index managed by the owner
        owner->remove_from_zindex(this);

        // Unload the music stream to free audio resources
        UnloadMusicStream(menu_music);
    }
    void TitleScreen::close_settings_menu()
    {
        if (settings_screen != nullptr)
        {
            delete settings_screen;
            settings_screen = nullptr;
        }
    }

    float TitleScreen::calculate_background_scale() const
    {
        if (sky_clouds_background_image == nullptr)
            return 0.0f;
        return static_cast<float>(GetScreenHeight()) / static_cast<float>(sky_clouds_background_image->height);
    }
    int TitleScreen::calculate_required_backgrounds() const
    {
        if (sky_clouds_background_image == nullptr)
            return 0;
        const float scaled_width = static_cast<float>(sky_clouds_background_image->width) * calculate_background_scale();
        return static_cast<int>(static_cast<float>(GetScreenWidth()) / scaled_width) + 2;
    }
    float TitleScreen::calculate_background_scale(const Texture2D *texture)
    {
        if (texture == nullptr)
            return 0.0f;
        return static_cast<float>(GetScreenHeight()) / static_cast<float>(texture->height);
    }
    int TitleScreen::calculate_required_backgrounds(const Texture2D *texture, const float scale)
    {
        if (texture == nullptr)
            return 0;
        const float scaled_width = static_cast<float>(texture->width) * scale;
        return static_cast<int>(static_cast<float>(GetScreenWidth()) / scaled_width) + 2;
    }

} // namespace artifact
