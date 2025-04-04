#pragma once
#include <memory>
#include "menu_base.h"
#include "ui/components/button_component.h"
#include "ui/components/containers/vertical_list_container.h"

namespace artifact
{
    class DeathScreen final : public MenuBase
    {
        bool is_being_destroyed = false;
        std::unique_ptr<VerticalListContainer> button_container;
        Texture2D title_image{};

    public:
        explicit DeathScreen(Stage *owner);
        void draw() override;
        void update(int mouse_x, int mouse_y) override;
        void destroy() override;
    };
} // namespace artifact
