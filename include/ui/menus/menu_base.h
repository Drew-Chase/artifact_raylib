#pragma once
#include "game.h"
#include "ui/components/component_base.h"

namespace artifact
{
    class MenuBase : public ComponentBase
    {
    public:
        explicit MenuBase(const char *identifier) : ComponentBase(identifier) {}
        bool is_menu_in_focus() const
        {
            const MenuBase *menu_in_focus = Game::get_instance()->get_stage_manager()->get_current_stage()->get_menu_in_focus();
            return menu_in_focus == this;
        }
    };
} // namespace artifact
