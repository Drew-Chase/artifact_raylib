
#include "game_utilities.h"

namespace artifact
{
    unsigned int GameUtilities::ConvertSecondsToFrames(const float seconds, const float deltaTime)
    {
        if (seconds == 0 || deltaTime == 0)return 0;
        return static_cast<unsigned int>(seconds / deltaTime);
    }
} // namespace artifact
