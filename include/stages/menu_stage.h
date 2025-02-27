#pragma once
#include "../ui/menus/menu_base.h"
#include "stage.h"

namespace artifact
{
    class MenuStage : public Stage, public MenuBase
    {
    public:
        explicit MenuStage(const char *identifier) : Stage(identifier), MenuBase(identifier) {}
    };
} // namespace artifact
