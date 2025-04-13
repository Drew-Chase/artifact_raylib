#include "ui/menus/death_screen.h"
#include <spdlog/fmt/bundled/format.h>
#include "game.h"
#include "resources/texture/menus/title_screen/artifact_logo.h"
#include "stages/playable_stage.h"
#include "stages/stages.h"

namespace artifact
{
    DeathScreen::DeathScreen(Stage *owner) :
        MenuBase("death_screen", owner)
    {
        // UI Settings
        constexpr auto text_color = WHITE;
        const Color button_normal_bg_color = ColorAlpha(BLACK, 0.5f);
        const Color button_hover_bg_color = ColorAlpha(BLACK, 0.75f);
        constexpr auto button_pressed_bg_color = BLACK;
        constexpr int font_size = 18;
        owner->push_to_zindex(this);
        title_image = LoadTextureFromImage(artifact_logo);



        // Create the vertical container for buttons
        constexpr int button_height = 70;
        const int button_width = GetScreenWidth() / 4;
        constexpr int button_spacing = 10;
        constexpr int container_padding = 10;

        button_container = std::make_unique<VerticalListContainer>("button_container", owner);

        button_container->set_gap(button_spacing);
        button_container->set_padding(container_padding);
        button_container->set_background_color(BLANK);

        // Create buttons
        auto respawn_button = std::make_unique<ButtonComponent>(
                "respawn_button",
                owner,
                button_width,
                button_height,
                "Respawn",
                [this]
                {
                    if (const auto level = dynamic_cast<PlayableStage *>(this->owner); level != nullptr)
                    {
                        level->respawn();
                    }
                });


        auto exit_button = std::make_unique<ButtonComponent>(
                "exit_button",
                owner,
                button_width,
                button_height,
                "Exit to Main Menu",
                []
                { Game::get_instance()->get_stage_manager()->load_stage(Stages::TITLE_SCREEN); });

        // Configure button appearances
        respawn_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);
        exit_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);

        respawn_button->set_font_size(font_size);
        exit_button->set_font_size(font_size);

        // Add buttons to container
        button_container->add_component(respawn_button.release());
        button_container->add_component(exit_button.release());

        button_container->auto_size();
    }
    void DeathScreen::draw()
    {
        MenuBase::draw();
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(RED, 0.5f));
        // Draw title
        int width = -1;
        int height = static_cast<int>(static_cast<double>(GetScreenHeight()) / 1.5);
        scale_texture(width, height, title_image);

        constexpr int y = 0;
        const int x = (GetScreenWidth() - width) / 2;
        draw_texture_scaled(width, height, x, y, title_image);

        // Draw the button container and its contents
        if (button_container)
            button_container->draw();

        DrawText(fmt::format("Artifact v{}", VERSION).c_str(), 10, GetScreenHeight() - 20, 16, ColorAlpha(WHITE, 0.5f));
    }
    void DeathScreen::update(const int mouse_x, const int mouse_y)
    {
        MenuBase::update(mouse_x, mouse_y);
        if (is_being_destroyed)
            return;
        if (button_container && this->is_menu_in_focus())
        {
            button_container->update(GetMouseX(), GetMouseY());
            button_container->set_position(GetScreenWidth() / 2 - button_container->get_width() / 2, GetScreenHeight() - button_container->get_height() - 20);
        }
    }
    void DeathScreen::destroy()
    {
        MenuBase::destroy();
        if (is_being_destroyed)
            return;
        is_being_destroyed = true;

        // Clear UI components before parent destroy
        button_container->destroy();
        button_container.reset();
        button_container = nullptr;
    }
} // namespace artifact
