#pragma once
#include "ui/components/containers/container_base.h"

namespace artifact
{
    class VerticalListContainer : public ContainerBase
    {
        int x;
        int y;
        int width;
        int height;
        int gap;
        int padding_top;
        int padding_bottom;
        int padding_left;
        int padding_right;
        Color background_color;

    public:
        VerticalListContainer(const char *identifier, int x, int y, int width, int height, int gap = 0, int padding = 0, Color background_color = BLANK);

        void draw() override;
        void update(int mouse_x, int mouse_y) override;

        // Setters
        void set_gap(const int gap) { this->gap = gap; }
        void set_padding(int padding);
        void set_padding(int top, int bottom, int left, int right);
        void set_background_color(const Color color) { this->background_color = color; }
        void set_position(int x, int y);
        void set_size(int width, int height);
        void auto_height();
        void auto_width();
        void auto_size();

        [[nodiscard]] int get_x() const { return x; }
        [[nodiscard]] int get_y() const { return y; }
        [[nodiscard]] int get_width() const { return width; }
        [[nodiscard]] int get_height() const { return height; }
        [[nodiscard]] int get_gap() const { return gap; }
        [[nodiscard]] int get_padding_top() const { return padding_top; }
        [[nodiscard]] int get_padding_bottom() const { return padding_bottom; }
        [[nodiscard]] int get_padding_left() const { return padding_left; }
        [[nodiscard]] int get_padding_right() const { return padding_right; }
        [[nodiscard]] const Color &get_background_color() const { return background_color; }
    };
} // namespace artifact
