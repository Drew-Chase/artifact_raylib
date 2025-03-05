// title_screen.h
#pragma once
#include <memory>
#include <raylib.h>
#include "menu_stage.h"
#include "ui/components/button_component.h"
#include "ui/components/containers/vertical_list_container.h" // Add this include

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

        // Images
        Texture2D *background_image = nullptr;
        Texture2D *title_image = nullptr;

        // Components
        std::unique_ptr<VerticalListContainer> button_container;
        std::unique_ptr<ButtonComponent> start_button;
        std::unique_ptr<ButtonComponent> exit_button;

    public:
        explicit TitleScreen() : MenuStage("title_screen") {}

        void draw() const override;
        void update() const override;
        void startup() override;
        void destroy() override;
    };
} // namespace artifact
