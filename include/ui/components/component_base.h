#pragma once
#include <raylib.h>

namespace artifact
{
    class ComponentBase
    {
        const char *identifier;

    public:
        virtual ~ComponentBase() = default;
        explicit ComponentBase(const char *identifier) : identifier(identifier) {}
        virtual void draw(int width, int height, int x, int y) {}
        virtual void update(int mouse_x, int mouse_y) {}
        static void draw_texture_to_fill_rect(int width, int height, int x, int y, const Texture2D &texture);
        virtual const char *get_identifier() { return identifier; }
    };
} // namespace artifact
