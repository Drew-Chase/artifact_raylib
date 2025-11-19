#include "../include/stages/stage_manager.h"
#include "stages/level_1_a_stage.h"
#include "stages/level_1_b_stage.h"
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
void artifact::StageManager::request_stage_change(const Stages stage, const Vector2 position)
{
    pending_stage_change = true;
    pending_stage = stage;
    pending_position = position;
}

void artifact::StageManager::process_pending_stage_change()
{
    if (!pending_stage_change)
        return;

    load_stage(pending_stage, pending_position);
    pending_stage_change = false;
}

artifact::Stage *artifact::StageManager::load_stage(const Stages stage, const Vector2 position)
{
    // destroy the current stage
    if (current_stage != nullptr)
        current_stage->destroy();

    switch (stage)
    {
        case Stages::LEVEL1A:
            current_stage = new Level1AStage();
            break;
        case Stages::LEVEL1B:
            current_stage = new Level1BStage();
            break;

        default:
        case Stages::TITLE_SCREEN:
            current_stage = new TitleScreen();
            break;
    }

    current_stage->startup();
    if (auto stage = dynamic_cast<PlayableStage *>(current_stage); position.x != 0 && position.y != 0)
    {
        stage->get_player()->set_position(position.x, position.y);
    }
    return current_stage;
}
