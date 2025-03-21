#pragma once
#include <cstdarg>
#include "settings/controls_settings.h"
#include "settings/display_settings.h"
#include "stages/stage_manager.h"

namespace artifact
{
    class Game
    {
        // Properties
        StageManager *manager;
        bool isRunning = true;

        Game();
        ~Game();
        // Add static instance
        static Game *instance;
        static void register_log_callback(int msgType, const char *message, va_list args);

    public:
        // Properties
        mutable DisplaySettings *display_settings = nullptr;
        mutable ControlsSettings *controls_settings = nullptr;
        bool debug_mode = false;

        // Get singleton instance
        static Game *get_instance();


        void exit_game() { isRunning = false; }
        StageManager *get_stage_manager() const { return manager; }
        static void run();
    };

} // namespace artifact
