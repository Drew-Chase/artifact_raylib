#pragma once
#include <raylib.h>

#include "stages/stage.h"

namespace artifact
{
    class ComponentBase
    {

    protected:
        const char *identifier;
        bool is_focused = false;
        Stage *owner;

    public:
        virtual ~ComponentBase() = default;
        explicit ComponentBase(const char *identifier, Stage *owner) : identifier(identifier), owner(owner) {}
        virtual void draw() {}
        virtual void update(int mouse_x, int mouse_y) {}
        static void draw_texture_to_fill_rect(int width, int height, int x, int y, const Texture2D &texture);
        static void draw_texture_scaled(float scale, float x, float y, const Texture2D &texture);
        static void draw_texture_scaled(int width, int height, int x, int y, const Texture2D &texture);
        virtual const char *get_identifier() { return identifier; }
        void set_focused(const bool is_focused) { this->is_focused = is_focused; }
        const char *get_identifier() const { return this->identifier; }
    };
} // namespace artifact
