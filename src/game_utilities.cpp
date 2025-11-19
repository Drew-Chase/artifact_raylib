
#include "game_utilities.h"

namespace artifact
{
    unsigned int GameUtilities::ConvertSecondsToFrames(const float seconds, const float delta_time)
    {
        if (seconds == 0 || delta_time == 0)return 0;
        return static_cast<unsigned int>(seconds / delta_time);
    }
} // namespace artifact
