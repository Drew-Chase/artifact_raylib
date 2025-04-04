
#include "features/teleporter_feature.h"

#include "game.h"

namespace artifact
{
    TeleporterFeature::TeleporterFeature(const Vector2 position, const Vector2 destination_position, const Stages destination_stage) :
        destination_stage(destination_stage), destination_position(destination_position), position(position)
    {
        sheet = new SpriteSheet("game/texture/features/teleporter_%d.png", 9, 13);
        collider = std::make_unique<Collider>(
                position.x,
                position.y,
                40,
                40,
                [destination_stage, position](Entity *entity)
                {
                    if (  PlayerEntity *player = dynamic_cast<PlayerEntity *>(entity))
                    {
                        if (destination_stage != Stages::NONE)
                            Game::get_instance()->get_stage_manager()->load_stage(destination_stage, position);
                        else
                        {
                            player->set_position(position.x, position.y);
                        }
                    }
                });
    }
    void TeleporterFeature::draw() const
    {
        if (sheet)
            sheet->draw(position);
    }
    void TeleporterFeature::update(const float delta_time)
    {
        if (sheet)
            sheet->update(delta_time);
    }
} // namespace artifact
