#pragma once
#include "ui/components/containers/vertical_list_container.h"

namespace artifact
{
    class DisplaySettingsComponent final : public VerticalListContainer
    {
    public:
        DisplaySettingsComponent(const char *identifier, Stage *owner) :
            VerticalListContainer(identifier, owner) {}
    };
} // namespace artifact
