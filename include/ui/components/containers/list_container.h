#pragma once
#include "ui/components/containers/container_base.h"

namespace artifact
{
    class ListContainer : public ContainerBase
    {
    protected:
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
        ListContainer(const char *identifier, Stage *owner, int x, int y, int width, int height, int gap = 0, int padding = 0, Color background_color = BLANK);

        void draw() override;
        void update(int mouse_x, int mouse_y) override;

        // Setters
        void set_gap(const int gap) { this->gap = gap; }
        void set_padding(int padding);
        void set_padding(int top, int bottom, int left, int right);
        void set_background_color(const Color color) { this->background_color = color; }
        void set_position(int x, int y);
        void set_size(int width, int height);
        virtual void auto_height();
        virtual void auto_width();
        virtual void auto_size();

        int get_x() const;
        int get_y() const;
        int get_width() const;
        int get_height() const;
        int get_gap() const;
        int get_padding_top() const;
        int get_padding_bottom() const;
        int get_padding_left() const;
        int get_padding_right() const;
        const Color &get_background_color() const;
    };
} // namespace artifact
