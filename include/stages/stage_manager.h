#pragma once
#include "stage.h"

namespace artifact
{
    class StageManager
    {
        Stage *current_stage = nullptr;

    public:
        StageManager();
        ~StageManager();
        Stage *loadStage(const char *identifier);
        Stage *getCurrentStage() const { return current_stage; }
    };
} // namespace artifact
