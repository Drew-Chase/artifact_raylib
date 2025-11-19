#include "ui/menus/settings_screen.h"
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include "game.h"
#include "stages/playable_stage.h"
#include "stages/title_screen.h"

namespace artifact
{
    SettingsScreen::SettingsScreen(Stage *owner) :
        MenuBase("settings_screen", owner)
    {
        display_settings = *Game::get_instance()->display_settings;
    }

    SettingsScreen::~SettingsScreen()
    {
        // First ensure all our resources are cleared
        save_apply_button.reset();
        back_button.reset();
        settings_menu_actions_container.reset();
        settings_tabs_container.reset();
        settings_container.reset();

        // Mark as pending removal to prevent any further updates
        pending_removal = true;
    }

    void SettingsScreen::draw()
    {
        if (pending_removal)
            return;

        // Draw semi-transparent background
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.7f));

        // Draw settings title
        DrawText("Settings", GetScreenWidth() / 2 - MeasureText("Settings", 30) / 2, 30, 30, WHITE);

        // Draw tab containers
        if (settings_tabs_container != nullptr)
            settings_tabs_container->draw();

        // Draw settings container
        if (settings_container != nullptr)
        {
            settings_container->set_background_color(RED);
            settings_container->draw();
        }

        // Draw action buttons
        if (settings_menu_actions_container != nullptr)
            settings_menu_actions_container->draw();
    }

    void SettingsScreen::update(const int mouse_x, const int mouse_y)
    {
        if (pending_removal && owner)
        {
            if (auto *title_screen = dynamic_cast<TitleScreen *>(owner); title_screen != nullptr)
                title_screen->close_settings_menu();
            if (const auto *stage = dynamic_cast<PlayableStage *>(owner); stage != nullptr)
                stage->pause_screen->close_settings_menu();
        }

        // Update settings tabs
        if (settings_tabs_container != nullptr)
        {
            settings_tabs_container->update(mouse_x, mouse_y);
            settings_tabs_container->set_position(GetScreenWidth() / 2 - settings_tabs_container->get_width() / 2, 80);
        }

        // Update settings container
        if (settings_container != nullptr)
        {
            settings_container->set_position(GetScreenWidth() / 2 - settings_container->get_width() / 2, 160);
            settings_container->update(mouse_x, mouse_y);
        }
    }


    void SettingsScreen::save_apply() const
    {
        const Game *game = Game::get_instance();

        // Save and Apply display settings
        *game->display_settings = display_settings;
        game->display_settings->apply();
        game->display_settings->save();

        // Save controls settings
        game->controls_settings->save();

        // Show confirmation message (in a real implementation)
        SPDLOG_INFO("Settings saved and applied");
    }

    void SettingsScreen::destroy()
    {
        if (pending_removal)
            return;

        pending_removal = true;

        // Free the buttons (safe to call reset on nullptr)
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
