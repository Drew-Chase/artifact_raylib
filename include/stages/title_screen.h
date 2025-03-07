#pragma once
#include <memory>
#include <raylib.h>
#include "menu_stage.h"
#include "ui/components/button_component.h"
#include "ui/components/containers/vertical_list_container.h"

namespace artifact
{
    class TitleScreen : public MenuStage
    {
        // UI Settings
        const Color background_color = Color(171, 217, 255);
        const Color text_color = WHITE;
        const Color button_normal_bg_color = ColorAlpha(BLACK, 0.5f);
        const Color button_hover_bg_color = ColorAlpha(BLACK, 0.75f);
        const Color button_pressed_bg_color = BLACK;

        const int font_size = 24;

        mutable float clouds_scroll = 0.0f;
        mutable float mountains_scroll = 0.0f;
        const float clouds_scroll_speed = 25.0f;
        const float mountains_scroll_speed = 75.0f;

        static float calculate_background_scale(const Texture2D *texture)
        {
            if (texture == nullptr)
                return 0.0f;
            return static_cast<float>(GetScreenHeight()) / static_cast<float>(texture->height);
        }

        static int calculate_required_backgrounds(const Texture2D *texture, const float scale)
        {
            if (texture == nullptr)
                return 0;
            // Calculate scaled width of the background
            const float scaled_width = static_cast<float>(texture->width) * scale;
            // Calculate how many images we need to cover the screen width plus one extra
            return static_cast<int>(static_cast<float>(GetScreenWidth()) / scaled_width) + 2;
        }


        // Images
        Texture2D *sky_clouds_background_image = nullptr;
        Texture2D *mountain_hills_background_image = nullptr;
        Texture2D *title_image = nullptr;

        // Sounds
        Music menu_music;

        // Components
        std::unique_ptr<VerticalListContainer> button_container;
        std::unique_ptr<ButtonComponent> start_button;
        std::unique_ptr<ButtonComponent> settings_button;
        std::unique_ptr<ButtonComponent> exit_button;

        float calculate_background_scale() const
        {
            if (sky_clouds_background_image == nullptr)
                return 0.0f;
            return static_cast<float>(GetScreenHeight()) / static_cast<float>(sky_clouds_background_image->height);
        }

        int calculate_required_backgrounds() const
        {
            if (sky_clouds_background_image == nullptr)
                return 0;
            // Calculate scaled width of the background
            const float scaled_width = static_cast<float>(sky_clouds_background_image->width) * calculate_background_scale();
            // Calculate how many images we need to cover the screen width plus one extra
            return static_cast<int>(static_cast<float>(GetScreenWidth()) / scaled_width) + 2;
        }

    public:
        explicit TitleScreen() : MenuStage("title_screen") {}

        void draw() const override;
        void update() const override;
        void startup() override;
        void destroy() override;
    };
} // namespace artifact
