#pragma once
#include "stage.h"
#include "ui/menus/menu_base.h"

namespace artifact
{
    class MenuStage : public Stage, public MenuBase
    {
    public:
        explicit MenuStage(const char *identifier) : Stage(identifier), MenuBase(identifier, this) {}
        ~MenuStage() override = default;
    };
} // namespace artifact
