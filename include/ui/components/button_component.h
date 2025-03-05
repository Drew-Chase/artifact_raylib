#pragma once
#include "ui/components/component_base.h"
#include <functional>

namespace artifact {
    class ButtonComponent : public ComponentBase {
        Rectangle bounds;
        bool isHovered;
        bool isPressed;
        std::function<void()> onClick;
        Color normalColor{};
        Color hoverColor{};
        Color pressedColor{};
        const char* text;

    public:
        ButtonComponent(const char* identifier,
                       int x, int y,
                       int width, int height,
                       const char* buttonText,
                       std::function<void()> clickHandler);

        void draw( ) override;
        void update(int mouseX, int mouseY) override;

        // Setters for customization
        void setColors(Color normal, Color hover, Color pressed);
    };
}