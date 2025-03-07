#pragma once
#include "list_container.h"
#include "ui/components/containers/container_base.h"

namespace artifact
{
    class HorizontalListContainer : public ListContainer
    {

    public:
        HorizontalListContainer(const char *identifier, Stage *owner, float x, float y, float width, float height, float gap = 0.0f, float padding = 0.0f, Color background_color = BLANK);

        void draw() override;
    };
} // namespace artifact
