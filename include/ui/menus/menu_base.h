#pragma once
#include "ui/components/component_base.h"

namespace artifact
{
    class MenuBase:public ComponentBase
    {
    public:
        explicit MenuBase(const char *identifier) : ComponentBase(identifier) {}
    };
} // namespace artifact
