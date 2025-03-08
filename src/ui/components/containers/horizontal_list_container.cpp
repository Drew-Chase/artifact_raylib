#include "ui/components/containers/horizontal_list_container.h"

#include <ranges>

#include "ui/components/button_component.h"

namespace artifact
{
    HorizontalListContainer::HorizontalListContainer(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const int gap, const int padding, const Color background_color) : ListContainer(identifier, owner, x, y, width, height, gap, padding, background_color) {}

    void HorizontalListContainer::draw()
    {
        if (background_color.a != 0)
        {
            DrawRectangle(x, y, width, height, background_color);
        }

        float current_x = x + padding_left;

        for (const auto &it: std::ranges::reverse_view(entries()))
        {
            if (auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                button->set_position(current_x, y + padding_top);
                button->set_height(height - padding_top - padding_bottom);
                button->draw();
                current_x += button->get_width() + gap;
            }
        }
    }
    void HorizontalListContainer::auto_width()
    {
        int current_x = x + padding_left;
        for (const auto &it: std::ranges::reverse_view(entries()))
        {
            if (const auto *button = dynamic_cast<ButtonComponent *>(it))
            {
                current_x += button->get_width() + gap;
            }
        }
        this->width = current_x - x - padding_left + padding_right;
    }
} // namespace artifact
