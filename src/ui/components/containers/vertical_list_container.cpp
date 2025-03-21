#include "ui/components/containers/vertical_list_container.h"
#include <algorithm> // For std::clamp
#include <ranges>
#include "ui/components/button_component.h"

namespace artifact
{
    VerticalListContainer::VerticalListContainer(const char *identifier, Stage *owner, const int x, const int y, const int width, const int height, const int gap, const int padding, const Color background_color) : ListContainer(identifier, owner, x, y, width, height, gap, padding, background_color) {}
    VerticalListContainer::VerticalListContainer(const char *identifier, Stage *owner) : ListContainer(identifier, owner, 0, 0, 0, 0, 0, 0, BLANK) {}

    int VerticalListContainer::calculate_content_height()
    {
        int content_height = padding_top + padding_bottom;
        for (const auto &component: components)
        {
            if (const auto *button = dynamic_cast<ButtonComponent *>(component.get()))
            {
                content_height += button->get_height() + gap;
            }
        }
        if (!components.empty())
            content_height -= gap; // Remove the last gap

        return content_height;
    }

    bool VerticalListContainer::needs_scrollbar() { return calculate_content_height() > height; }

    void VerticalListContainer::draw()
    {
        // Draw the container background at the exact specified dimensions
        if (background_color.a != 0)
        {
            DrawRectangle(x, y, width, height, background_color);
        }

        // Check if we need a scrollbar
        has_scrollbar = needs_scrollbar();

        // Calculate available content width
        int content_width = width - padding_left - padding_right;

        // If we have a scrollbar, reduce the content width
        if (has_scrollbar)
            content_width -= scroll_width;

        // Apply scissor mode to clip content to the container's visible area
        BeginScissorMode(x, y, width, height);

        int current_y = y + padding_top - static_cast<int>(scroll_offset);

        for (const auto &component: components)
        {
            if (auto *button = dynamic_cast<ButtonComponent *>(component.get()))
            {
                button->set_position(x + padding_left, current_y);
                button->set_width(content_width);

                // Only draw if within visible area (with a small margin)
                if (current_y + button->get_height() >= y - 50 && current_y <= y + height + 50)
                    button->draw();

                current_y += button->get_height() + gap;
            }
        }

        EndScissorMode();

        // Draw the scrollbar if needed
        if (has_scrollbar)
        {
            // Draw scrollbar track (black rectangle)
            scrollbar_track = {static_cast<float>(x + width - scroll_width), static_cast<float>(y), static_cast<float>(scroll_width), static_cast<float>(height)};
            DrawRectangleRec(scrollbar_track, BLACK);

            // Calculate content height and scroll parameters
            int content_height = calculate_content_height();
            scroll_max = std::max(0, content_height - height);

            // Calculate and draw thumb (white rectangle)
            float thumb_height = height * height / static_cast<float>(content_height);
            thumb_height = std::max(20.0f, thumb_height); // Minimum thumb size

            float thumb_position_ratio = scroll_offset / scroll_max;
            float thumb_y = y + (height - thumb_height) * thumb_position_ratio;

            scrollbar_thumb = {static_cast<float>(x + width - scroll_width), thumb_y, static_cast<float>(scroll_width), thumb_height};
            DrawRectangleRec(scrollbar_thumb, WHITE);
        }
    }

    void VerticalListContainer::update(int mouse_x, int mouse_y)
    {
        // Check if we need a scrollbar
        has_scrollbar = needs_scrollbar();

        if (has_scrollbar)
        {
            // Handle scrollbar interaction
            const int mouse_wheel_move = GetMouseWheelMove();
            if (mouse_wheel_move != 0)
            {
                scroll_offset -= mouse_wheel_move * 30.0f;
            }

            // Handle scrollbar thumb drag
            if (CheckCollisionPointRec({static_cast<float>(mouse_x), static_cast<float>(mouse_y)}, scrollbar_thumb))
            {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    is_scrolling = true;
                }
            }

            if (is_scrolling)
            {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    float drag_pos = mouse_y - y;
                    float drag_ratio = drag_pos / static_cast<float>(height);
                    scroll_offset = drag_ratio * scroll_max;
                } else
                {
                    is_scrolling = false;
                }
            }

            // Clamp scroll_offset
            int content_height = calculate_content_height();
            scroll_max = std::max(0, content_height - height);
            scroll_offset = std::clamp(scroll_offset, 0.0f, scroll_max);

            // Adjust mouse position for components based on scroll offset
            const int adjusted_mouse_y = mouse_y + static_cast<int>(scroll_offset);

            // Update components with adjusted mouse coordinates
            for (const auto &component: components)
            {
                // Only update components within or near the visible area
                int comp_y = component->get_y();
                int comp_height = component->get_height();

                if (comp_y + comp_height >= y - static_cast<int>(scroll_offset) - 50 && comp_y <= y + height - static_cast<int>(scroll_offset) + 50)
                {
                    component->update(mouse_x, adjusted_mouse_y);
                }
            }
        } else
        {
            // No scrollbar, update all components normally
            ListContainer::update(mouse_x, mouse_y);
            scroll_offset = 0.0f;
        }
    }

    void VerticalListContainer::auto_height()
    {
        int content_height = calculate_content_height();
        this->height = content_height;
    }
} // namespace artifact
