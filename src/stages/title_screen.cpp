// title_screen.cpp
#include "../include/stages/title_screen.h"
#include <fmt/format.h>
#include <raylib.h>
#include <spdlog/spdlog.h>
#include "game.h"

#include <resources/texture/menus/title_screen/artifact_logo.h>
#include <resources/texture/menus/title_screen/sunny_mountains_sky.h>
#include <resources/texture/menus/title_screen/sunny_mountains_hills.h>

namespace artifact
{
    void TitleScreen::startup()
    {
        owner->push_to_zindex(this);
        sky_clouds_background_image = LoadTextureFromImage(sunny_mountains_sky);
        mountain_hills_background_image = LoadTextureFromImage(sunny_mountains_hills);
        title_image = LoadTextureFromImage(artifact_logo);
        // Pre-calculate title size and position.
        int title_width = -1;
        int title_height = static_cast<int>(static_cast<double>(GetScreenHeight()) / 1.5);
        scale_texture(title_width, title_height, title_image);
        title_image_rect = Rectangle{static_cast<float>(GetScreenWidth() - title_width) / 2, 0, static_cast<float>(title_width), static_cast<float>(title_height)};

        // Create the vertical container for buttons
        constexpr int button_height = 70;
        const int button_width = GetScreenWidth() / 4;
        constexpr int button_spacing = 10;
        constexpr int container_padding = 10;

        button_container = std::make_unique<VerticalListContainer>("button_container", this);

        button_container->set_gap(button_spacing);
        button_container->set_padding(container_padding);
        button_container->set_background_color(BLANK);

        // Create buttons
        auto start_button = std::make_unique<ButtonComponent>("start_button", this, button_width, button_height, "Start Game",
                                                              []
                                                              {
                                                                  SPDLOG_INFO("Start button clicked!");
                                                                  Game::get_instance()->get_stage_manager()->load_stage(Stages::LEVEL1A);
                                                              });

        auto settings_button = std::make_unique<ButtonComponent>("settings_button", this, button_width, button_height, "Settings Game",
                                                                 [this]
                                                                 {
                                                                     SPDLOG_INFO("Settings button clicked!");
                                                                     settings_screen = std::make_unique<SettingsScreen>(this);
                                                                 });

        auto exit_button = std::make_unique<ButtonComponent>("exit_button", this, button_width, button_height, "Exit Game",
                                                             []
                                                             {
                                                                 SPDLOG_INFO("Exit button clicked!");
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
        button_container->add_component(start_button.release());
        button_container->add_component(settings_button.release());
        button_container->add_component(exit_button.release());

        button_container->auto_size();

        // Play theme music
        menu_music = LoadMusicStream("game/audio/music/mainmenu.ogg");
        menu_music.looping = true;
        PlayMusicStream(menu_music);
    }
    void TitleScreen::draw() const
    {
        if (is_being_destroyed)
            return;
        ClearBackground(BLACK);
        draw_background();

        if (settings_screen != nullptr)
        {
            if (!settings_screen->is_being_removed())
                settings_screen->draw();
        } else
        {
            draw_texture_scaled(title_image_rect.width, title_image_rect.height, title_image_rect.x, title_image_rect.y, title_image, title_image_tint);

            // Draw the button container and its contents
            if (button_container)
                button_container->draw();
        }

        DrawText(fmt::format("Artifact v{}", VERSION).c_str(), 10, GetScreenHeight() - 20, 16, ColorAlpha(WHITE, 0.5f));
    }
    void TitleScreen::update(const float delta_time)
    {
        if (is_being_destroyed)
            return;
        UpdateMusicStream(menu_music);
        update_background(delta_time);

        if (settings_screen != nullptr && settings_screen)
        {
            if (!settings_screen->is_being_removed())
                settings_screen->update(GetMouseX(), GetMouseY());
            else
                settings_screen.reset();
        } else
        {
            if (is_loaded)
            {
                int title_width = -1;
                int title_height = static_cast<int>(static_cast<double>(GetScreenHeight()) / 1.5);
                scale_texture(title_width, title_height, title_image);
                title_image_rect = Rectangle{static_cast<float>(GetScreenWidth() - title_width) / 2, 0, static_cast<float>(title_width), static_cast<float>(title_height)};

                if (button_container && this->is_menu_in_focus())
                    button_container->update(GetMouseX(), GetMouseY());
                button_container->set_position(GetScreenWidth() / 2 - button_container->get_width() / 2, GetScreenHeight() - button_container->get_height() - 20);
            } else
            {
                tick_animate_fadein(delta_time);
            }
        }
    }
    void TitleScreen::draw_background() const
    {
        // Draw clouds background layer
        const float clouds_scale = calculate_background_scale(sky_clouds_background_image);
        const float scaled_clouds_width = static_cast<float>(sky_clouds_background_image.width) * clouds_scale;
        const int num_clouds = calculate_required_backgrounds(&sky_clouds_background_image, clouds_scale);

        for (int i = 0; i < num_clouds; i++)
        {
            draw_texture_scaled(clouds_scale, clouds_scroll + (static_cast<float>(i) * scaled_clouds_width), 0, sky_clouds_background_image);
        }

        // Draw mountains background layer
        const float mountains_scale = calculate_background_scale(mountain_hills_background_image);
        const float scaled_mountains_width = static_cast<float>(mountain_hills_background_image.width) * mountains_scale;
        const int num_mountains = calculate_required_backgrounds(&mountain_hills_background_image, mountains_scale);

        for (int i = 0; i < num_mountains; i++)
        {
            draw_texture_scaled(mountains_scale, mountains_scroll + (static_cast<float>(i) * scaled_mountains_width), 0, mountain_hills_background_image);
        }
    }
    void TitleScreen::update_background(const float delta_time) const
    {

        // Update clouds scroll
        const float clouds_scale = calculate_background_scale(sky_clouds_background_image);
        const float scaled_clouds_width = static_cast<float>(sky_clouds_background_image.width) * clouds_scale;

        clouds_scroll -= clouds_scroll_speed * delta_time;
        if (clouds_scroll <= -scaled_clouds_width)
        {
            clouds_scroll = 0.0f;
        }

        // Update mountains scroll
        const float mountains_scale = calculate_background_scale(mountain_hills_background_image);
        const float scaled_mountains_width = static_cast<float>(mountain_hills_background_image.width) * mountains_scale;

        mountains_scroll -= mountains_scroll_speed * delta_time;
        if (mountains_scroll <= -scaled_mountains_width)
        {
            mountains_scroll = 0.0f;
        }
    }
    void TitleScreen::destroy()
    {
        Stage::destroy();
        if (is_being_destroyed)
            return;
        is_being_destroyed = true;
        // Make sure to explicitly clean up textures
        UnloadTexture(sky_clouds_background_image);
        UnloadTexture(mountain_hills_background_image);
        UnloadTexture(title_image);

        // Clean up music resource
        if (IsMusicStreamPlaying(menu_music))
            StopMusicStream(menu_music);
        UnloadMusicStream(menu_music);

        // Delete settings_screen if it exists
        if (settings_screen != nullptr)
        {
            settings_screen->destroy();
        }

        // Clear UI components before parent destroy
        button_container->destroy();
        button_container.reset();
        button_container = nullptr;
    }
    void TitleScreen::close_settings_menu()
    {
        if (settings_screen != nullptr)
        {
            settings_screen.reset();
        }
    }

    float TitleScreen::calculate_background_scale() const { return static_cast<float>(GetScreenHeight()) / static_cast<float>(sky_clouds_background_image.height); }
    int TitleScreen::calculate_required_backgrounds() const
    {
        const float scaled_width = static_cast<float>(sky_clouds_background_image.width) * calculate_background_scale();
        return static_cast<int>(static_cast<float>(GetScreenWidth()) / scaled_width) + 2;
    }
    float TitleScreen::calculate_background_scale(const Texture2D &texture) { return static_cast<float>(GetScreenHeight()) / static_cast<float>(texture.height); }
    int TitleScreen::calculate_required_backgrounds(const Texture2D *texture, const float scale)
    {
        if (texture == nullptr)
            return 0;
        const float scaled_width = static_cast<float>(texture->width) * scale;
        return static_cast<int>(static_cast<float>(GetScreenWidth()) / scaled_width) + 2;
    }
    void TitleScreen::tick_animate_fadein(const float delta_time)
    {
        // Increment elapsed time and calculate progress
        fade_in_elapsed_time_ms += static_cast<size_t>(delta_time * 1000.0f); // Convert delta_time to milliseconds
        float progress = 0.0f;

        // Maintain start parameters until the start delay elapses
        if (constexpr unsigned int start_delay = 1000; fade_in_elapsed_time_ms >= start_delay)
        {
            constexpr unsigned int animation_duration = 1000;
            progress = static_cast<float>(fade_in_elapsed_time_ms - start_delay) / animation_duration;
        }

        if (progress > 1.0f)
        {
            progress = 1.0f;
            is_loaded = true; // Animation completed
        }

        // Calculate easing for the slide and opacity effect
        const float eased_progress = progress * (2.0f - progress); // Ease-out quadratic

        // Title image opacity and position
        constexpr int final_title_y = 0;
        const int start_title_y = static_cast<int>(GetScreenHeight() * 0.1f); // 10% below the final position
        const int title_y = static_cast<int>(start_title_y + (final_title_y - start_title_y) * eased_progress);

        // Draw title image with animation
        int title_width = -1;
        int title_height = static_cast<int>(static_cast<double>(GetScreenHeight()) / 1.5);
        scale_texture(title_width, title_height, title_image);
        const int title_x = (GetScreenWidth() - title_width) / 2;
        title_image_rect = Rectangle{static_cast<float>(title_x), static_cast<float>(title_y), static_cast<float>(title_width), static_cast<float>(title_height)};
        title_image_tint = ColorAlpha(WHITE, eased_progress);

        // Buttons opacity and vertical position
        const int final_button_y = GetScreenHeight() - button_container->get_height() - 20;
        const int start_button_y = final_button_y + static_cast<int>(GetScreenHeight() * 0.1f); // 10% below the final position
        const int button_y = static_cast<int>(start_button_y + (final_button_y - start_button_y) * eased_progress);

        // Calculate the alpha relative to the final alpha and the current progress.
        const Color button_background_color = ColorAlpha(button_normal_bg_color, eased_progress * 0.5f);
        const Color new_text_color = ColorAlpha(text_color, eased_progress);

        // Update and draw buttons with animation
        for (const auto &component: button_container->get_components())
        {
            if (const auto button = dynamic_cast<ButtonComponent *>(component.get()))
            {
                button->set_normal_color(button_background_color);
                button->set_text_color(new_text_color);
            }
        }
        button_container->set_position(GetScreenWidth() / 2 - button_container->get_width() / 2, button_y);
    }

} // namespace artifact
