#include "ui/menus/menu_base.h"
artifact::MenuBase::~MenuBase()
{
    if (const MenuBase *menu_in_focus = owner->get_menu_in_focus(); menu_in_focus == this)
    {
        owner->remove_from_zindex(this);
    }

}
bool artifact::MenuBase::is_menu_in_focus() const
{
    const MenuBase *menu_in_focus = owner->get_menu_in_focus();
    return menu_in_focus == this;
}
