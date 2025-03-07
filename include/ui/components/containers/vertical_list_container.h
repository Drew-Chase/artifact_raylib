#pragma once
#include "list_container.h"
#include "ui/components/containers/container_base.h"

namespace artifact
{
    class VerticalListContainer final : public ListContainer
    {
    public:
        VerticalListContainer(const char *identifier, Stage *owner, int x, int y, int width, int height, int gap = 0, int padding = 0, Color background_color = BLANK);
        void draw() override;
    };
} // namespace artifact
