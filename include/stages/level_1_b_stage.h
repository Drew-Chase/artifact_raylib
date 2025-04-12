#pragma once
#include "features/teleporter_feature.h"
#include "playable_stage.h"

namespace artifact {
class Level1BStage final : public PlayableStage{

    Music music{};
    TeleporterFeature* nextlvl_teleporter = nullptr;
    TeleporterFeature* secret_teleporter = nullptr;
public:
    explicit Level1BStage();
    void draw() const override;
    void update(float delta_time) override;
    void destroy() override;
    void startup() override;
    Vector2 get_spawn_position() const override;
    void spawn_entities() override;
};
} // artifact
