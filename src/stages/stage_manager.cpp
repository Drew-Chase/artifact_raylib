#include "../include/stages/stage_manager.h"
artifact::StageManager::StageManager() {}
artifact::StageManager::~StageManager() { delete this->current_stage; }
artifact::Stage *artifact::StageManager::loadStage(const char *identifier)
{
    const auto stage = new Stage(identifier);
    stage->update(true);
    stage->draw(true);
    this->current_stage = stage;
    return stage;
}
