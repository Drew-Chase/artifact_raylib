#pragma once
#include "ui/components/containers/list_container.h"

namespace artifact
{
    class VerticalListContainer final : public ListContainer
    {
    public:
        VerticalListContainer(const char *identifier, Stage *owner, int x, int y, int width, int height, int gap = 0, int padding = 0, Color background_color = BLANK);
        void draw() override;
        void auto_height() override;
    };
} // namespace artifact
