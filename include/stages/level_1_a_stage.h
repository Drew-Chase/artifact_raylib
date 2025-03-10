#pragma once
#include "playable_stage.h"

namespace artifact {
class Level1AStage :public PlayableStage{

public:
    void draw() const override;
    void update(float deltaTime) const override;
    void destroy() override;
    void startup() override;
};
} // artifact
