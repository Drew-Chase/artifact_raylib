#pragma once
#include "features/teleporter_feature.h"
#include "playable_stage.h"

namespace artifact
{
    class Level1AStage final : public PlayableStage
    {
        Music music{};
        TeleporterFeature* lvl2_teleporter = nullptr;
        TeleporterFeature* secret_teleporter = nullptr;
        TeleporterFeature* test_teleporter = nullptr;
    public:
        explicit Level1AStage();
        void draw() const override;
        void update(float delta_time) override;
        void destroy() override;
        void startup() override;
        Vector2 get_spawn_position() const override;
        void spawn_entities() override;
    };
} // namespace artifact
