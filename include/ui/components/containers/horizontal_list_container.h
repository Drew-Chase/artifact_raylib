#pragma once
#include "ui/components/containers/list_container.h"

namespace artifact
{
    class HorizontalListContainer final : public ListContainer
    {

    public:
        HorizontalListContainer(const char *identifier, Stage *owner, int x, int y, int width, int height, int gap = 0.0f, int padding = 0.0f, Color background_color = BLANK);
        HorizontalListContainer(const char *identifier, Stage *owner);
        void draw() override;
        void auto_width() override;
        void auto_size() override;
    };
} // namespace artifact
