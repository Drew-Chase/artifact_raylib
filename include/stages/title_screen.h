#pragma once
#include <memory>
#include <raylib.h>
#include "menu_stage.h"
#include "ui/components/button_component.h"
#include "ui/components/containers/vertical_list_container.h"
#include "ui/menus/settings_screen.h"

namespace artifact
{
    class TitleScreen final : public MenuStage
    {
        // UI Settings
        const Color text_color = WHITE;
        const Color button_normal_bg_color = ColorAlpha(BLACK, 0.5f);
        const Color button_hover_bg_color = ColorAlpha(BLACK, 0.75f);
        const Color button_pressed_bg_color = BLACK;
        const int font_size = 18;

        mutable float clouds_scroll = 0.0f;
        mutable float mountains_scroll = 0.0f;
        const float clouds_scroll_speed = 25.0f;
        const float mountains_scroll_speed = 75.0f;

        // Additional Screens
        std::unique_ptr<SettingsScreen> settings_screen = nullptr;

        // Images
        Texture2D sky_clouds_background_image{};
        Texture2D mountain_hills_background_image{};
        Texture2D title_image{};

        // Sounds
        Music menu_music;

        // Components
        std::unique_ptr<VerticalListContainer> button_container;
        std::unique_ptr<ButtonComponent> start_button;
        std::unique_ptr<ButtonComponent> settings_button;
        std::unique_ptr<ButtonComponent> exit_button;

        // Component functions
        void update_background(float deltaTime) const;
        void draw_background() const;

        // Utility functions
        float calculate_background_scale() const;
        int calculate_required_backgrounds() const;
        static float calculate_background_scale(const Texture2D &texture);
        static int calculate_required_backgrounds(const Texture2D *texture, float scale);

    public:
        TitleScreen() : MenuStage("TitleScreen"), menu_music() {}
        void draw() const override;
        void update(float deltaTime) override;
        void startup() override;
        void destroy() override;
        void close_settings_menu();
    };
} // namespace artifact
