#pragma once

namespace artifact
{
    class ComponentBase
    {
        const char *identifier;

    public:
        explicit ComponentBase(const char *identifier) { this->identifier = identifier; }
        void draw(int width, int height, int x, int y, int mouse_x, int mouse_y);
    };
} // namespace artifact
