#pragma once
#include "menu_base.h"
#include "settings_screen.h"
#include "ui/components/containers/vertical_list_container.h"

namespace artifact
{
    class PauseScreen final : MenuBase
    {
        bool is_being_destroyed = false;
        std::unique_ptr<VerticalListContainer> button_container;
        Texture2D title_image{};
        std::unique_ptr<SettingsScreen> settings_screen = nullptr;

    public:
        explicit PauseScreen(const char *identifier, Stage *owner);
        void draw() override;
        void update(int mouse_x, int mouse_y) override;
        void destroy() override;
        void close_settings_menu();
    };
} // namespace artifact
