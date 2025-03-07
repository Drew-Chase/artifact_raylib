#include "ui/components/containers/horizontal_list_container.h"

namespace artifact
{
    HorizontalListContainer::HorizontalListContainer(const char *identifier, Stage *owner, const float x, const float y, const float width, const float height, const float gap, const float padding, const Color background_color) : ListContainer(identifier, owner, x, y, width, height, gap, padding, background_color) {}

    void HorizontalListContainer::draw()
    {
        if (background_color.a != 0)
        {
            DrawRectangle(x, y, width, height, background_color);
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
} // namespace artifact
