#pragma once
#include "menu_base.h"

namespace artifact
{
    class SettingsScreen final : public MenuBase
    {
    public:
        explicit SettingsScreen(const char *identifier, Stage* owner) : MenuBase(identifier, owner) {}
    };
} // namespace artifact
