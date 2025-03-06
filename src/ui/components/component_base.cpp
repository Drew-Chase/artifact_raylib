#include "ui/components/component_base.h"

#include <algorithm>

void artifact::ComponentBase::draw_texture_to_fill_rect(const int width, const int height, const int x, const int y, const Texture2D &texture)
{
    // Calculate scaling factors for both dimensions
    const float scaleX = static_cast<float>(width) / static_cast<float>(texture.width);
    const float scaleY = static_cast<float>(height) / static_cast<float>(texture.height);

    // Use the larger scale to ensure the image covers the whole screen
    const float scale = std::max(scaleX, scaleY);

    // Calculate the scaled dimensions
    const float scaledWidth = static_cast<float>(texture.width) * scale;
    const float scaledHeight = static_cast<float>(texture.height) * scale;

    // Calculate position to center the image
    const float dx = (static_cast<float>(width) - scaledWidth) * 0.5f;
    const float dy = (static_cast<float>(height) - scaledHeight) * 0.5f;

    // Define source rectangle (the entire texture)
    const Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};

    // Define destination rectangle (where and how big to draw it)
    const Rectangle dest = {dx, dy, scaledWidth, scaledHeight};

    // Draw the texture
    DrawTexturePro(texture, source, dest, {static_cast<float>(x), static_cast<float>(y)}, 0.0f, WHITE);
}
void artifact::ComponentBase::draw_texture_scaled(const float scale, const float x, const float y, const Texture2D &texture)
{
    const float scaledWidth = static_cast<float>(texture.width) * scale;
    const float scaledHeight = static_cast<float>(texture.height) * scale;

    const Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    const Rectangle dest = {x, y, scaledWidth, scaledHeight};

    DrawTexturePro(texture, source, dest, {0.0f, 0.0f}, 0.0f, WHITE);
}
void artifact::ComponentBase::draw_texture_scaled(const int width, const int height, const int x, const int y, const Texture2D &texture)
{
    int adjustedWidth = width;
    int adjustedHeight = height;

    if (width <= 0 && height > 0)
    {
        adjustedWidth = static_cast<int>(static_cast<float>(height) * (static_cast<float>(texture.width) / static_cast<float>(texture.height)));
    } else if (height <= 0 && width > 0)
    {
        adjustedHeight = static_cast<int>(static_cast<float>(width) * (static_cast<float>(texture.height) / static_cast<float>(texture.width)));
    }

    const float scaleX = static_cast<float>(adjustedWidth) / static_cast<float>(texture.width);
    const float scaleY = static_cast<float>(adjustedHeight) / static_cast<float>(texture.height);
    const float scale = std::min(scaleX, scaleY);
    const float scaledWidth = static_cast<float>(texture.width) * scale;
    const float scaledHeight = static_cast<float>(texture.height) * scale;
    const float dx = (static_cast<float>(adjustedWidth) - scaledWidth) * 0.5f + static_cast<float>(x);
    const float dy = (static_cast<float>(adjustedHeight) - scaledHeight) * 0.5f + static_cast<float>(y);
    const Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    const Rectangle dest = {dx, dy, scaledWidth, scaledHeight};

    DrawTexturePro(texture, source, dest, {0.0f, 0.0f}, 0.0f, WHITE);
}
