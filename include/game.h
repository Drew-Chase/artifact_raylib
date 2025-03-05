#pragma once
#include <cstdarg>

#include "stages/stage_manager.h"

namespace artifact
{
    class Game
    {
        StageManager *manager;
        Game(); // Keep constructor private
        ~Game(); // Keep destructor private

        // Add static instance
        static Game *instance;
        static void register_log_callback(int msgType, const char *message, va_list args);
        bool isRunning = true;

    public:
        // Get singleton instance
        static Game *get_instance();
        void exit_game() { isRunning = false; }


        // Replace run with static method that uses singleton
        static void run();
        [[nodiscard]] StageManager *get_stage_manager() const { return manager; }
    };

} // namespace artifact
