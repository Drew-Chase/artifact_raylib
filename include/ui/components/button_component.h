#pragma once
#include <functional>
#include "ui/components/component_base.h"

namespace artifact
{
    class ButtonComponent : public ComponentBase
    {
        bool is_hovered;
        bool is_pressed;
        std::function<void()> on_click;
        Color normal_color{};
        Color hover_color{};
        Color pressed_color{};
        Color text_color{};
        const char *text;
        int font_size = 12;

    public:
        ButtonComponent(const char *identifier, Stage *owner, int x, int y, int width, int height, const char *buttonText, std::function<void()> clickHandler);

        void draw() override;
        void update(int mouseX, int mouseY) override;

        // Setters for customization
        void set_colors(Color normal, Color hover, Color pressed, Color text);
        void set_normal_color(Color color);
        void set_hover_color(Color color);
        void set_pressed_color(Color color);
        void set_text_color(Color color);
        void set_font_size(int size);
        void set_on_click(std::function<void()> onClick);
        void set_text(const char *text);
    };
} // namespace artifact
