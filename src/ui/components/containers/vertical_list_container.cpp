#include "ui/components/containers/vertical_list_container.h"
#include <ranges>
#include "ui/components/button_component.h"

namespace artifact
{
    VerticalListContainer::VerticalListContainer(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const int gap, const int padding, const Color background_color) : ListContainer(identifier, owner, x, y, width, height, gap, padding, background_color) {}

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


} // namespace artifact
