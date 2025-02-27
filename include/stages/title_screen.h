#pragma once
#include "menu_stage.h"

namespace artifact
{
    class TitleScreen : public MenuStage
    {
    public:
        explicit TitleScreen() : MenuStage("title_screen") {}

        void draw() const override;
        void update() const override;
    };
} // namespace artifact
