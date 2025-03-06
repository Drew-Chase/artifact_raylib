#pragma once
#include "ui/menus/menu_base.h"


namespace artifact
{
    class Stage
    {
        const char *identifier;
        const MenuBase *menu_in_focus = nullptr;

    public:
        explicit Stage(const char *identifier) : identifier(identifier) {}

        virtual ~Stage() = default;

        virtual void draw() const { draw(false); }
        virtual void draw(bool first_draw) const {}
        virtual void update() const { update(false); }
        virtual void update(bool first_update) const {}
        virtual void startup() {}
        virtual void destroy() {}

        const char *get_identifier() const { return this->identifier; }
        void set_menu_in_focus(const MenuBase *menu_in_focus) { this->menu_in_focus = menu_in_focus; }
        const MenuBase *get_menu_in_focus() const { return this->menu_in_focus; }
    };
} // namespace artifact
