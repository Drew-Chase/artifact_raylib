
#include "ui/components/containers/list_container.h"
#include <iostream>
#include "ui/components/button_component.h"

namespace artifact
{
    ListContainer::ListContainer(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const int gap, const int padding, const Color background_color) : ContainerBase(identifier, owner), x(x), y(y), width(width), height(height), gap(gap), padding_top(padding), padding_bottom(padding), padding_left(padding), padding_right(padding), background_color(background_color) {}
    void ListContainer::draw() { ContainerBase::draw(); }
    void ListContainer::update(const int mouse_x, const int mouse_y)
    {
        for (const auto components = entries(); auto *component: components)
        {
            if (component != nullptr && component != reinterpret_cast<ComponentBase *>(-1))
                component->update(mouse_x, mouse_y);
        }
    }

    void ListContainer::set_padding(const int padding) { padding_top = padding_bottom = padding_left = padding_right = padding; }

    void ListContainer::set_padding(const int top, const int bottom, const int left, const int right)
    {
        padding_top = top;
        padding_bottom = bottom;
        padding_left = left;
        padding_right = right;
    }

    void ListContainer::set_position(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }

    void ListContainer::set_size(const int width, const int height)
    {
        this->width = width;
        this->height = height;
    }
    void ListContainer::auto_height()
    {
        int largest_height = 0;
        for (const auto &it: entries())
        {
            if (const auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                largest_height = std::max(largest_height, button->get_height());
            }
        }
        this->height = largest_height + padding_top + padding_bottom;
    }
    void ListContainer::auto_width()
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
    void ListContainer::auto_size()
    {
        auto_width();
        auto_height();
    }
    void ListContainer::set_height(const int height)
    {
        ContainerBase::set_height(height);
        this->set_position(width, height);
    }
    void ListContainer::set_width(const int width)
    {
        ContainerBase::set_width(width);
        this->set_position(width, height);
    }
    int ListContainer::get_x() const { return x; }
    int ListContainer::get_y() const { return y; }
    int ListContainer::get_width() const { return width; }
    int ListContainer::get_height() const { return height; }
    int ListContainer::get_gap() const { return gap; }
    int ListContainer::get_padding_top() const { return padding_top; }
    int ListContainer::get_padding_bottom() const { return padding_bottom; }
    int ListContainer::get_padding_left() const { return padding_left; }
    int ListContainer::get_padding_right() const { return padding_right; }
    const Color &ListContainer::get_background_color() const { return background_color; }
} // namespace artifact
