
#include "ui/components/button_component.h"

namespace artifact
{
    ButtonComponent::ButtonComponent(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const char *buttonText, std::function<void()> clickHandler) : ComponentBase(identifier, owner), bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, isHovered(false), isPressed(false), onClick(std::move(clickHandler)), text(buttonText)
    {
        // Default colors
        normalColor = LIGHTGRAY;
        hoverColor = GRAY;
        pressedColor = DARKGRAY;
    }

    void ButtonComponent::draw()
    {
        Color currentColor = normalColor;
        if (isPressed)
            currentColor = pressedColor;
        else if (isHovered)
            currentColor = hoverColor;

        DrawRectangleRec(bounds, currentColor);

        // Draw text centered in button
        const int textWidth = MeasureText(text, fontSize);
        const int textX = static_cast<int>(bounds.x + (bounds.width - static_cast<float>(textWidth)) / 2);
        const int textY = static_cast<int>(bounds.y + (bounds.height - static_cast<float>(this->fontSize)) / 2);

        DrawText(text, textX, textY, fontSize, textColor);
    }

    void ButtonComponent::update(const int mouseX, const int mouseY)
    {
        const Vector2 mousePoint = {static_cast<float>(mouseX), static_cast<float>(mouseY)};
        isHovered = CheckCollisionPointRec(mousePoint, bounds);

        if (isHovered)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isPressed = true;
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && isPressed)
            {
                if (onClick)
                {
                    onClick();
                }
                isPressed = false;
            }
        } else
        {
            isPressed = false;
        }
    }
    void ButtonComponent::set_colors(const Color normal, const Color hover, const Color pressed, const Color text)
    {
        normalColor = normal;
        hoverColor = hover;
        pressedColor = pressed;
        textColor = text;
    }

    void ButtonComponent::set_normal_color(const Color color) { normalColor = color; }

    void ButtonComponent::set_hover_color(const Color color) { hoverColor = color; }

    void ButtonComponent::set_pressed_color(const Color color) { pressedColor = color; }

    void ButtonComponent::set_text_color(const Color color) { textColor = color; }

    void ButtonComponent::set_font_size(const int size) { fontSize = size; }

    void ButtonComponent::set_on_click(std::function<void()> onClick) { this->onClick = std::move(onClick); }

    void ButtonComponent::set_text(const char *text) { this->text = text; }
    void ButtonComponent::set_width(const int width) { bounds.width = static_cast<float>(width); }
    void ButtonComponent::set_height(const int height) { bounds.height = static_cast<float>(height); }
    void ButtonComponent::set_position(const int x, const int y)
    {
        bounds.x = static_cast<float>(x);
        bounds.y = static_cast<float>(y);
    }
    int ButtonComponent::get_height() const { return static_cast<int>(bounds.height); }
    int ButtonComponent::get_width() const { return static_cast<int>(bounds.width); }

} // namespace artifact
