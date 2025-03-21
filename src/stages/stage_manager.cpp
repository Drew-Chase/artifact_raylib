#include "../include/stages/stage_manager.h"

#include "stages/level_1_a_stage.h"
#include "stages/title_screen.h"

artifact::StageManager::StageManager() = default;
artifact::StageManager::~StageManager()
{
    if (current_stage != nullptr)
    {
        current_stage->destroy();
        current_stage = nullptr;
        delete current_stage;
    }
}
artifact::Stage *artifact::StageManager::load_stage(const Stages stage)
{
    // destroy the current stage
    if (current_stage != nullptr)
        current_stage->destroy();

    switch (stage)
    {
        case Stages::LEVEL1A:
            current_stage = new Level1AStage();
            break;

        default:
        case Stages::TITLE_SCREEN:
            current_stage = new TitleScreen();
            break;
    }

    current_stage->startup();
    return current_stage;
}
