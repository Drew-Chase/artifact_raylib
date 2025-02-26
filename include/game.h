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
        Game(const Game &) = delete;
        Game &operator=(const Game &) = delete;

        // Add static instance
        static Game *instance;
        static void SpdLoggerCallback(int msgType, const char* message, va_list args);

    public:
        // Get singleton instance
        static Game *getInstance();

        // Replace run with static method that uses singleton
        static void run();
        StageManager *getManager() const { return manager; }
    };
} // namespace artifact
