#pragma once

namespace artifact
{
    class GameUtilities
    {

    public:
        /**
         * Calculates the number of frames that should elapse over 'x' seconds
         * @param seconds The number of seconds that the frames should elapse over
         * @param delta_time The number of milliseconds since the last frame (60fps = 16.666ms)
         * @return The amount of frames that should elapse over 'x' seconds
         */
        static unsigned int ConvertSecondsToFrames(float seconds, float delta_time);
    };
} // namespace artifact
