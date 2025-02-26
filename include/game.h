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

        // Delete copy constructor and assignment operator

        // Add static instance
        static Game *instance;
        static void SpdLoggerCallback(int msgType, const char *message, va_list args);

    public:
        // Get singleton instance
        static Game *getInstance();

        Game(const Game &) = delete;
        Game &operator=(const Game &) = delete;

        // Replace run with static method that uses singleton
        static void run();
        [[nodiscard]] StageManager *getManager() const { return manager; }
    };

} // namespace artifact
