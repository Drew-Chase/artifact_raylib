
#include "ui/menus/settings_screen.h"
#include <fmt/format.h>
#include "game.h"
#include "stages/title_screen.h"

namespace artifact
{
    SettingsScreen::SettingsScreen(Stage *owner) : MenuBase("settings_screen", owner)
    {
        display_settings = *Game::get_instance()->display_settings;
        setup_action_buttons();
        // setup_settings_tabs();
    }
    SettingsScreen::~SettingsScreen()
    {
        destroy();
    }
    void SettingsScreen::draw()
    {
        if (pending_removal)
        {
            return;
        }
        if (settings_menu_actions_container != nullptr)
            settings_menu_actions_container->draw();
    }
    void SettingsScreen::update(const int mouse_x, const int mouse_y)
    {
        if (pending_removal && owner)
        {
            dynamic_cast<TitleScreen *>(owner)->close_settings_menu();
        }


        if (settings_menu_actions_container != nullptr)
        {
            settings_menu_actions_container->update(mouse_x, mouse_y);
            settings_menu_actions_container->set_position(GetScreenWidth() / 2 - settings_menu_actions_container->get_width() / 2, GetScreenHeight() - settings_menu_actions_container->get_height() - 20);
        }
    }
    void SettingsScreen::setup_action_buttons()
    {
        constexpr int button_height = 70;
        const int button_width = GetScreenWidth() / 4;
        constexpr int button_spacing = 10;
        constexpr int container_padding = 10;

        settings_menu_actions_container = std::make_unique<HorizontalListContainer>("settings_menu_actions_container", owner);

        settings_menu_actions_container->set_gap(button_spacing);
        settings_menu_actions_container->set_padding(container_padding);
        settings_menu_actions_container->set_background_color(BLANK);

        save_apply_button = std::make_unique<ButtonComponent>("settings_save_apply", owner, 0, 0, button_width, button_height, "Save & Apply", [&] { save_apply(); });
        back_button = std::make_unique<ButtonComponent>("settings_back", owner, 0, 0, button_width, button_height, "Back", [this] { pending_removal = true; });

        // Configure button appearances
        save_apply_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);
        back_button->set_colors(button_normal_bg_color, button_hover_bg_color, button_pressed_bg_color, text_color);

        save_apply_button->set_font_size(font_size);
        back_button->set_font_size(font_size);

        settings_menu_actions_container->add_component(save_apply_button.release());
        settings_menu_actions_container->add_component(back_button.release());

        settings_menu_actions_container->auto_size();
    }
    void SettingsScreen::setup_settings_tabs()
    {
        for (int i = 0; i <= 3; i++)
        {
            const auto tab = static_cast<SettingsTab>(i);
            const char *label;
            switch (tab)
            {
                case SettingsTab::DISPLAY:
                    label = "Display";
                    break;
                case SettingsTab::AUDIO:
                    label = "Audio";
                    break;
                case SettingsTab::CONTROLS:
                    label = "Controls";
                    break;
                case SettingsTab::VIDEO:
                    label = "Video";
                    break;
            }
            TraceLog(LOG_DEBUG, "tab: %d, label: %s", i, label);
            // settings_tabs_container->add_component<ButtonComponent>(fmt::format("settings_tab_{}", i).c_str(), owner, 0, 0, 0, 0, label, [&] { current_tab = tab; });
        }
    }
    void SettingsScreen::save_apply()
    {
        const Game *game = Game::get_instance();

        // Save and Apply display settings.
        game->display_settings = &display_settings;
        game->display_settings->apply();
        game->display_settings->save();
    }
    void SettingsScreen::destroy()
    {
        pending_removal = true;

        // Free the buttons.
        save_apply_button.reset();
        back_button.reset();

        // Clear all components from containers first
        if (settings_menu_actions_container)
        {
            settings_menu_actions_container->destroy();
            settings_menu_actions_container.reset();
        }
        if (settings_tabs_container)
        {
            settings_tabs_container->destroy();
            settings_tabs_container.reset();
        }
        if (settings_container)
        {
            settings_container->destroy();
            settings_container.reset();
        }
    }
    bool SettingsScreen::is_being_removed() const { return pending_removal; }
} // namespace artifact
