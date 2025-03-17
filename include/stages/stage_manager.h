#pragma once
#include "stage.h"
#include "stages.h"

namespace artifact
{
    class StageManager
    {
        Stage *current_stage = nullptr;

    public:
        StageManager();
        ~StageManager();

        Stage *load_stage(Stages stage);
        [[nodiscard]] Stage *get_current_stage() const { return current_stage; }
    };
} // namespace artifact
