#include "ui/components/component_base.h"

#include <algorithm>

void artifact::ComponentBase::draw_texture_to_fill_rect(const float width, const float height, const float x, const float y, const Texture2D &texture)
{
    // Calculate scaling factors for both dimensions
    const float scaleX = width / texture.width;
    const float scaleY = height / texture.height;

    // Use the larger scale to ensure the image covers the whole screen
    const float scale = std::max(scaleX, scaleY);

    // Calculate the scaled dimensions
    const float scaledWidth = texture.width * scale;
    const float scaledHeight = texture.height * scale;

    // Calculate position to center the image
    const float dx = (width - scaledWidth) * 0.5f;
    const float dy = (height - scaledHeight) * 0.5f;

    // Define source rectangle (the entire texture)
    const Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};

    // Define destination rectangle (where and how big to draw it)
    const Rectangle dest = {dx, dy, scaledWidth, scaledHeight};

    // Draw the texture
    DrawTexturePro(texture, source, dest, {x, y}, 0.0f, WHITE);
}
