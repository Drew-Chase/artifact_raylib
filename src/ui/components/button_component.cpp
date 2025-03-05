
#include "ui/components/button_component.h"

namespace artifact
{
    ButtonComponent::ButtonComponent(const char *identifier, int x, int y, int width, int height, const char *buttonText, std::function<void()> clickHandler) : ComponentBase(identifier), bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, isHovered(false), isPressed(false), onClick(std::move(clickHandler)), text(buttonText)
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
        const int fontSize = 20;
        const int textWidth = MeasureText(text, fontSize);
        const int textX = static_cast<int>(bounds.x + (bounds.width - textWidth) / 2);
        const int textY = static_cast<int>(bounds.y + (bounds.height - fontSize) / 2);

        DrawText(text, textX, textY, fontSize, BLACK);
    }

    void ButtonComponent::update(int mouseX, int mouseY)
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

    void ButtonComponent::setColors(Color normal, Color hover, Color pressed)
    {
        normalColor = normal;
        hoverColor = hover;
        pressedColor = pressed;
    }
} // namespace artifact
