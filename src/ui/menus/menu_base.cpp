#include "ui/menus/menu_base.h"
artifact::MenuBase::~MenuBase()
{
    if (const MenuBase *menu_in_focus = owner->peek_zindex(); menu_in_focus == this)
    {
        owner->remove_from_zindex(this);
    }

}
bool artifact::MenuBase::is_menu_in_focus() const
{
    const MenuBase *menu_in_focus = owner->peek_zindex();
    return menu_in_focus == this;
}
