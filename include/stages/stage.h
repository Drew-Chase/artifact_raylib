#pragma once
#include <algorithm>
#include <vector>

namespace artifact
{
    class MenuBase;
    class Stage
    {
        const char *identifier;
        std::vector<const MenuBase *> zindex;

    public:
        explicit Stage(const char *identifier) : identifier(identifier) {}
        virtual ~Stage() = default;

        virtual void draw() const { draw(false); }
        virtual void draw(bool first_draw) const {}
        virtual void update() const { update(false); }
        virtual void update(bool first_update) const {}
        virtual void startup() {}
        virtual void destroy() {}

        virtual const char *get_identifier() const { return this->identifier; }
        virtual void set_menu_in_focus(const MenuBase *menu_in_focus) { zindex.push_back(menu_in_focus); }
        virtual const MenuBase *get_menu_in_focus() const { return zindex.back(); }
        virtual void remove_from_zindex(const MenuBase *menu)
        {
            if (const auto it = std::ranges::find(zindex, menu); it != zindex.end())
                zindex.erase(it);
        }
    };
} // namespace artifact
