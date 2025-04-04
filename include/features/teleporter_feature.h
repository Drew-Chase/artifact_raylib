#pragma once
#include <memory>
#include "collider.h"
#include "stages/playable_stage.h"
#include "stages/stages.h"

namespace artifact
{
    class TeleporterFeature
    {
        std::unique_ptr<Collider> collider;
        Stages destination_stage = Stages::NONE;
        Vector2 destination_position;
        Vector2 position;
        SpriteSheet *sheet;

    public:
        TeleporterFeature(Vector2 position, Vector2 destination_position, Stages destination_stage);
        TeleporterFeature(const Vector2 position, const Vector2 destination_position) :
            TeleporterFeature(position, destination_position, Stages::NONE) {}
        TeleporterFeature(const Vector2 position, const Stages destination_stage) :
            TeleporterFeature(position, {}, destination_stage) {}
        void draw() const;
        void update(float delta_time);
    };
} // namespace artifact
