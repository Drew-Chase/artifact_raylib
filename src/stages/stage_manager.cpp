#include "../include/stages/stage_manager.h"

artifact::StageManager::StageManager() {}
artifact::StageManager::~StageManager() { delete this->current_stage; }
