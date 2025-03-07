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

        virtual void draw() const {}
        virtual void update(float deltaTime) const {}
        virtual void startup() {}
        virtual void destroy() {}

        virtual const char *get_identifier() const { return this->identifier; }
        virtual void push_to_zindex(const MenuBase *menu) { zindex.push_back(menu); }
        virtual const MenuBase *peek_zindex() const
        {
            if (zindex.empty())
                return nullptr;
            return zindex.back();
        }
        virtual void remove_from_zindex(const MenuBase *menu)
        {
            if (const auto it = std::ranges::find(zindex, menu); it != zindex.end())
                zindex.erase(it);
        }
    };
} // namespace artifact
