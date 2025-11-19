#pragma once
#include <raylib.h>


#include "stage.h"
#include "stages.h"

namespace artifact
{
    class StageManager
    {
        Stage *current_stage = nullptr;
        bool pending_stage_change = false;
        Stages pending_stage;
        Vector2 pending_position = {};

        Stage *load_stage(Stages stage, Vector2 position = {});

    public:
        StageManager();
        ~StageManager();

        void request_stage_change(Stages stage, Vector2 position = {});
        void process_pending_stage_change();
        [[nodiscard]] bool has_pending_stage_change() const { return pending_stage_change; }
        [[nodiscard]] Stage *get_current_stage() const { return current_stage; }
    };
} // namespace artifact
