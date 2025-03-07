#pragma once
#include "ui/components/component_base.h"

namespace artifact
{
    class MenuBase : public ComponentBase
    {
    public:
        explicit MenuBase(const char *identifier, Stage *owner) : ComponentBase(identifier, owner) {}
        ~MenuBase() override;
        virtual void destroy(){}
        bool is_menu_in_focus() const;
    };
} // namespace artifact
