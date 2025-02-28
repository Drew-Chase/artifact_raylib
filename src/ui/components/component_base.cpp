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
