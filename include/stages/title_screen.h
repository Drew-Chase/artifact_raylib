#pragma once
#include <raylib.h>
#include "menu_stage.h"

namespace artifact
{
    class TitleScreen : public MenuStage
    {
        Texture2D *background_image = nullptr;

    public:
        explicit TitleScreen() : MenuStage("title_screen") {}

        void draw() const override;
        void update() const override;
        void startup() override;
        void destroy() override;
    };
} // namespace artifact
