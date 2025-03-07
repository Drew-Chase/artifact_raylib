#pragma once
#include <cstdarg>

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
        DisplaySettings *display_settings = nullptr;

        // Get singleton instance
        static Game *get_instance();


        void exit_game() { isRunning = false; }
        StageManager *get_stage_manager() const { return manager; }
        static void run();
    };

} // namespace artifact
