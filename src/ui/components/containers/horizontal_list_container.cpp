#include "ui/components/containers/horizontal_list_container.h"

namespace artifact
{
    HorizontalListContainer::HorizontalListContainer(const char *identifier, Stage *owner, const float x, const float y, const float width, const float height, const float gap, const float padding, const Color background_color) : ContainerBase(identifier, owner), x(x), y(y), width(width), height(height), gap(gap), padding_top(padding), padding_bottom(padding), padding_left(padding), padding_right(padding), background_color(background_color) {}

    void HorizontalListContainer::draw()
    {
        if (background_color.a != 0)
        {
            DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), background_color);
        }

        float current_x = x + padding_left;

        for (auto components = entries(); auto *component: components)
        {
            if (auto *base = component)
            {
                base->draw();
                current_x += gap;
            }
        }
    }

    void HorizontalListContainer::update(const int mouse_x, const int mouse_y)
    {
        for (auto components = entries(); auto *component: components)
        {
            component->update(mouse_x, mouse_y);
        }
    }

    void HorizontalListContainer::set_padding(const float padding) { padding_top = padding_bottom = padding_left = padding_right = padding; }

    void HorizontalListContainer::set_padding(const float top, const float bottom, const float left, const float right)
    {
        padding_top = top;
        padding_bottom = bottom;
        padding_left = left;
        padding_right = right;
    }

    void HorizontalListContainer::set_position(const float new_x, const float new_y)
    {
        x = new_x;
        y = new_y;
    }

    void HorizontalListContainer::set_size(const float new_width, const float new_height)
    {
        width = new_width;
        height = new_height;
    }
} // namespace artifact
