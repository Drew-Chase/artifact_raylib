#include <ranges>

#include "ui/components/containers/vertical_list_container.h"

#include "ui/components/button_component.h"

namespace artifact
{
    VerticalListContainer::VerticalListContainer(const char *identifier, const float x, const float y, const float width, const float height, const float gap, const float padding, const Color background_color) : ContainerBase(identifier), x(x), y(y), width(width), height(height), gap(gap), padding_top(padding), padding_bottom(padding), padding_left(padding), padding_right(padding), background_color(background_color) {}

    void VerticalListContainer::draw()
    {
        // Draw the background respecting the padding on all sides evenly
        DrawRectangle(x - padding_left, y - padding_top, width + padding_right, height + padding_bottom, background_color);

        float current_y = y + padding_top;

        for (const auto &it: std::ranges::reverse_view(entries()))
        {
            if (auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                button->set_position(x + padding_left, current_y);
                button->draw();
                current_y += button->get_height() + gap;
            }
        }
    }

    void VerticalListContainer::update(const int mouse_x, const int mouse_y)
    {
        for (auto components = entries(); auto *component: components)
        {
            component->update(mouse_x, mouse_y);
        }
    }

    void VerticalListContainer::set_padding(const float padding) { padding_top = padding_bottom = padding_left = padding_right = padding; }

    void VerticalListContainer::set_padding(const float top, const float bottom, const float left, const float right)
    {
        padding_top = top;
        padding_bottom = bottom;
        padding_left = left;
        padding_right = right;
    }

    void VerticalListContainer::set_position(const float x, const float y)
    {
        this->x = x;
        this->y = y;
    }

    void VerticalListContainer::set_size(const float width, const float height)
    {
        this->width = width;
        this->height = height;
    }
} // namespace artifact
