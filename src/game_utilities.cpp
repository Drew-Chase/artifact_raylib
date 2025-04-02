
#include "game_utilities.h"

namespace artifact {
    unsigned int GameUtilities::ConvertSecondsToFrames(const unsigned int seconds, const float deltaTime)
    {
        return static_cast<unsigned int>(seconds * (deltaTime * 100.f));
    }
} // artifact