#pragma once
#include <memory>
#include "collider.h"
#include "stages/playable_stage.h"
#include "stages/stages.h"

namespace artifact
{
    class TeleporterFeature
    {
        Stages destination_stage = Stages::NONE;
        Vector2 destination_position;
        Vector2 position;
        SpriteSheet *sheet;
        PlayableStage *owner;
        PlayerEntity *captured_player;

        Sound teleport_sfx{};

        float timer = 0.f;


    public:
        TeleporterFeature(PlayableStage *owner, Vector2 position, Vector2 destination_position, Stages destination_stage);
        TeleporterFeature(PlayableStage *owner, const Vector2 position, const Vector2 destination_position) :
            TeleporterFeature(owner, position, destination_position, Stages::NONE) {}
        TeleporterFeature(PlayableStage *owner, const Vector2 position, const Stages destination_stage) :
            TeleporterFeature(owner, position, {}, destination_stage) {}
        void draw() const;
        void update(float delta_time);
    };
} // namespace artifact
