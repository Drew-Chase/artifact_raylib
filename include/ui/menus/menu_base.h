#pragma once

namespace artifact
{
    class MenuBase
    {
        const char *identifier;

    public:
        explicit MenuBase(const char *identifier) { this->identifier = identifier; }
        void draw(int width, int height, int x, int y, int mouse_x, int mouse_y);
    };
} // namespace artifact
