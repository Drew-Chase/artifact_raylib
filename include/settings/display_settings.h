#pragma once
#include "settings_base.h"

namespace artifact
{
    enum class WindowMode
    {
        FULLSCREEN,
        WINDOWED,
        WINDOWED_FULLSCREEN,
    };
    class DisplaySettings final : public SettingsBase
    {

    public:
        // Display Settings
        WindowMode window_mode = WindowMode::FULLSCREEN;
        unsigned int screen_width = 1280;
        unsigned int screen_height = 720;
        unsigned int frame_rate = 60;
        bool vsync = true;

        // Functions
        explicit DisplaySettings();
        ~DisplaySettings() override;
        void load() override;
        void save() override;
        void apply() override;
        void reset() override;
    };
} // namespace artifact
