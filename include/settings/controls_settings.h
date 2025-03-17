#pragma once
#include "settings_base.h"

namespace artifact
{
    class ControlsSettings final : public SettingsBase
    {
    public:
        // Controls
        bool toggle_sprint;

        // Keybindings
        int movement_right;
        int movement_left;
        int movement_jump;
        int movement_sprint;
        int combat_light;
        int combat_dash;
        int menu_pause;


        explicit ControlsSettings();
        void load() override;
        void save() override;
        void reset() override;
        static bool pressed(int key);
        static bool down(int key);
        static bool up(int key);

        // Static functions
    };
} // namespace artifact
