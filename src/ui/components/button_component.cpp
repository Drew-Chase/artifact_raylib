#include "ui/components/button_component.h"

#include <string.h>

namespace artifact
{
    ButtonComponent::ButtonComponent(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const char *buttonText, std::function<void()> clickHandler) : ComponentBase(identifier, owner, x, y, width, height), is_hovered(false), is_pressed(false), on_click(std::move(clickHandler)), text(buttonText)
    {
        // Default colors
        normal_color = LIGHTGRAY;
        hover_color = GRAY;
        pressed_color = DARKGRAY;
        text_color = BLACK;
    }
    ButtonComponent::ButtonComponent(const char *identifier, Stage *owner, const int width, const int height, const char *buttonText, std::function<void()> clickHandler) : ButtonComponent(identifier, owner, 0, 0, width, height, buttonText, std::move(clickHandler)) {}

    void ButtonComponent::draw()
    {
        Color currentColor = normal_color;
        if (is_pressed)
            currentColor = pressed_color;
        else if (is_hovered)
            currentColor = hover_color;

        DrawRectangleRec(bounds, currentColor);

        // Draw text centered in button
        const int textWidth = MeasureText(text, font_size);
        const int textX = static_cast<int>(bounds.x + (bounds.width - static_cast<float>(textWidth)) / 2);
        const int textY = static_cast<int>(bounds.y + (bounds.height - static_cast<float>(this->font_size)) / 2);

        DrawText(text, textX, textY, font_size, text_color);
    }

    void ButtonComponent::update(const int mouseX, const int mouseY)
    {
        const Vector2 mousePoint = {static_cast<float>(mouseX), static_cast<float>(mouseY)};
        is_hovered = CheckCollisionPointRec(mousePoint, bounds);

        if (is_hovered)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                is_pressed = true;
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && is_pressed)
            {
                if (on_click)
                {
                    on_click();
                }
                is_pressed = false;
            }
        } else
        {
            is_pressed = false;
        }
    }

    void ButtonComponent::set_colors(const Color normal, const Color hover, const Color pressed, const Color text)
    {
        normal_color = normal;
        hover_color = hover;
        pressed_color = pressed;
        text_color = text;
    }

    void ButtonComponent::set_normal_color(const Color color) { normal_color = color; }

    void ButtonComponent::set_hover_color(const Color color) { hover_color = color; }

    void ButtonComponent::set_pressed_color(const Color color) { pressed_color = color; }

    void ButtonComponent::set_text_color(const Color color) { text_color = color; }

    void ButtonComponent::set_font_size(const int size) { font_size = size; }

    void ButtonComponent::set_on_click(std::function<void()> onClick) { this->on_click = std::move(onClick); }

    void ButtonComponent::set_text(const char *text)
    {
        this->text = text ? strdup(text) : nullptr;
    }

} // namespace artifact
