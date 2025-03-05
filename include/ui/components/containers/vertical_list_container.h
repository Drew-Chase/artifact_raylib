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
    };
} // namespace artifact
