#pragma once
#include <raylib.h>


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

        Stage *load_stage(Stages stage, Vector2 position = {});
        [[nodiscard]] Stage *get_current_stage() const { return current_stage; }
    };
} // namespace artifact
