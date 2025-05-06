#include "ui/components/containers/horizontal_list_container.h"
#include <ranges>
#include "ui/components/button_component.h"

namespace artifact
{
    HorizontalListContainer::HorizontalListContainer(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const int gap, const int padding, const Color background_color) :
        ListContainer(identifier, owner, x, y, width, height, gap, padding, background_color) {}
    HorizontalListContainer::HorizontalListContainer(const char *identifier, Stage *owner) :
        ListContainer(identifier, owner) {}

    void HorizontalListContainer::draw()
    {
        if (background_color.a != 0)
        {
            DrawRectangle(x, y, width, height, background_color);
        }

        if (components.empty())
        {
            return;
        }

        float current_x = x + padding_left;
        for (const auto &component: components)
        {
            component->set_position(current_x, y + padding_top);
            component->set_height(height - padding_top - padding_bottom);
            component->draw();
            current_x += component->get_width() + gap;
        }
    }
    void HorizontalListContainer::auto_width()
    {
        int current_x = x + padding_left;
        for (const auto &component: components)
        {
            if (const auto *button = dynamic_cast<ButtonComponent *>(component.get()))
            {
                current_x += button->get_width() + gap;
            }
        }
        this->width = current_x - x - padding_left + padding_right;
    }

    void HorizontalListContainer::auto_size()
    {
        // Calculate width based on components
        auto_width();

        // Calculate height based on the tallest component
        int max_height = padding_top + padding_bottom;
        for (const auto &component: components)
        {
            max_height = std::max(max_height, component->get_height() + padding_top + padding_bottom);
        }

        this->height = max_height;
    }

} // namespace artifact
