#pragma once
#include "ui/components/containers/container_base.h"

namespace artifact
{
    class HorizontalListContainer : public ContainerBase
    {
        float x;
        float y;
        float width;
        float height;
        float gap;
        float padding_top;
        float padding_bottom;
        float padding_left;
        float padding_right;
        Color background_color;

    public:
        HorizontalListContainer(const char *identifier, float x, float y, float width, float height, float gap = 0.0f, float padding = 0.0f, Color background_color = BLANK);

        void draw() override;
        void update(int mouse_x, int mouse_y) override;

        // Setters
        void set_gap(float gap) { this->gap = gap; }
        void set_padding(float padding);
        void set_padding(float top, float bottom, float left, float right);
        void set_background_color(Color color) { this->background_color = color; }
        void set_position(float x, float y);
        void set_size(float width, float height);
    };
} // namespace artifact
