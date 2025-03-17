#pragma once
#include "ui/components/containers/list_container.h"

namespace artifact
{
    class VerticalListContainer final : public ListContainer
    {
        bool has_scrollbar = false;
        float scroll_offset = 0.0f; // Current scroll position
        float scroll_max = 0.0f; // Maximum scroll value
        int scroll_width = 10; // Width of the scrollbar
        bool is_scrolling = false; // Flag to track scrolling state
        Rectangle scrollbar_track; // Rectangle for the scrollbar track
        Rectangle scrollbar_thumb; // Rectangle for the scrollbar thumb

    public:
        VerticalListContainer(const char *identifier, Stage *owner, int x, int y, int width, int height, int gap = 0, int padding = 0, Color background_color = BLANK);
        void draw() override;
        void update(int mouse_x, int mouse_y) override;
        void auto_height() override;

        int calculate_content_height();
        void set_scrollbar_width(int width) { scroll_width = width; }
        bool needs_scrollbar();
    };
} // namespace artifact
