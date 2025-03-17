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
        Rectangle bounds;

    public:
        virtual ~ComponentBase() = default;
        explicit ComponentBase(const char *identifier, Stage *owner);
        explicit ComponentBase(const char *identifier, Stage *owner, int x, int y, int width, int height);
        virtual void draw() {}
        virtual void update(int mouse_x, int mouse_y) {}
        static void draw_texture_to_fill_rect(int width, int height, int x, int y, const Texture2D &texture);
        static void draw_texture_scaled(float scale, float x, float y, const Texture2D &texture);
        static void draw_texture_scaled(int width, int height, int x, int y, const Texture2D &texture);
        static void scale_texture(int &width, int &height, const Texture2D &texture);

        virtual const char *get_identifier();
        void set_focused(bool is_focused);
        const char *get_identifier() const;

        virtual void set_width(int width);
        virtual void set_height(int height);
        virtual void set_position(int x, int y);
        virtual int get_height() const;
        virtual int get_width() const;
        virtual int get_x() const;
        virtual int get_y() const;
    };
} // namespace artifact
