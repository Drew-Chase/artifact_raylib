#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include "menu_stage.h"
#include "ui/components/button_component.h" // Add this include

namespace artifact
{
    class TitleScreen : public MenuStage
    {
        Texture2D *background_image = nullptr;
        std::unique_ptr<ButtonComponent> start_button;
        std::unique_ptr<ButtonComponent> exit_button;

    public:
        explicit TitleScreen() : MenuStage("title_screen") {}

        void draw() const override;
        void update() const override;
        void startup() override;
        void destroy() override;
    };
} // namespace artifact