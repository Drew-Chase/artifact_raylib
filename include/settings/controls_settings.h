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

        // Static functions
    };
} // namespace artifact
