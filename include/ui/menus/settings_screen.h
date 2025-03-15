#pragma once
#include <memory>


#include "menu_base.h"
#include "settings/display_settings.h"
#include "ui/components/button_component.h"
#include "ui/components/containers/horizontal_list_container.h"
#include "ui/components/containers/vertical_list_container.h"

namespace artifact
{
    enum class SettingsTab
    {
        DISPLAY,
        CONTROLS,
        AUDIO,
        VIDEO,
    };
    class SettingsScreen final : public MenuBase
    {
        // UI Settings
        const Color text_color = WHITE;
        const Color button_normal_bg_color = ColorAlpha(BLACK, 0.5f);
        const Color button_hover_bg_color = ColorAlpha(BLACK, 0.75f);
        const Color button_pressed_bg_color = BLACK;
        const int font_size = 16;
        SettingsTab current_tab = SettingsTab::DISPLAY;

        bool pending_removal = false;

        // Shadow Settings
        DisplaySettings display_settings;

        // Components
        std::unique_ptr<HorizontalListContainer> settings_tabs_container;
        std::unique_ptr<HorizontalListContainer> settings_menu_actions_container;
        std::unique_ptr<VerticalListContainer> settings_container;
        std::unique_ptr<ButtonComponent> save_apply_button;
        std::unique_ptr<ButtonComponent> back_button;

        void setup_action_buttons();
        void setup_settings_tabs();

        // Utility functions
        void save_apply();

    public:
        explicit SettingsScreen(Stage *owner);
        void draw() override;
        void update(int mouse_x, int mouse_y) override;
        void destroy() override;
    };
} // namespace artifact
