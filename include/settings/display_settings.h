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
        WindowMode window_mode;
        unsigned int screen_width;
        unsigned int screen_height;
        unsigned int frame_rate;
        bool vsync;

        // Functions
        explicit DisplaySettings();
        ~DisplaySettings() override;
        void load() override;
        void save() override;
        void apply() override;
        void reset() override;
    };
} // namespace artifact
