#include <ranges>

#include "ui/components/containers/vertical_list_container.h"

#include "ui/components/button_component.h"

namespace artifact
{
    VerticalListContainer::VerticalListContainer(const char *identifier, Stage* owner, const int x, const int y, const int width, const int height, const int gap, const int padding, const Color background_color) : ContainerBase(identifier, owner), x(x), y(y), width(width), height(height), gap(gap), padding_top(padding), padding_bottom(padding), padding_left(padding), padding_right(padding), background_color(background_color) {}

    void VerticalListContainer::draw()
    {
        // Draw the background respecting the padding on all sides evenly
        DrawRectangle(x - padding_left, y - padding_top, width + padding_left + padding_right, height + padding_top + padding_bottom, background_color);

        int current_y = y + padding_top;

        for (const auto &it: std::ranges::reverse_view(entries()))
        {
            if (auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                button->set_position(x + padding_left, current_y);
                button->set_width(width - padding_right - padding_left);
                button->draw();
                current_y += button->get_height() + gap;
            }
        }
    }

    void VerticalListContainer::update(const int mouse_x, const int mouse_y)
    {
        for (const auto components = entries(); auto *component: components)
        {
            component->update(mouse_x, mouse_y);
        }
    }

    void VerticalListContainer::set_padding(const int padding) { padding_top = padding_bottom = padding_left = padding_right = padding; }

    void VerticalListContainer::set_padding(const int top, const int bottom, const int left, const int right)
    {
        padding_top = top;
        padding_bottom = bottom;
        padding_left = left;
        padding_right = right;
    }

    void VerticalListContainer::set_position(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }

    void VerticalListContainer::set_size(const int width, const int height)
    {
        this->width = width;
        this->height = height;
    }
    void VerticalListContainer::auto_height()
    {
        int current_y = y + padding_top;
        for (const auto &it: std::ranges::reverse_view(entries()))
        {
            if (const auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                current_y += button->get_height() + gap;
            }
        }
        this->height = current_y - y - padding_top + padding_bottom;
    }
    void VerticalListContainer::auto_width()
    {
        int largest_width = 0;
        for (const auto &it: entries())
        {
            if (const auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                largest_width = std::max(largest_width, button->get_width());
            }
        }
        this->width = largest_width + padding_left + padding_right;
    }
    void VerticalListContainer::auto_size()
    {
        auto_width();
        auto_height();
    }
} // namespace artifact
