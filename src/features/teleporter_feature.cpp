
#include "features/teleporter_feature.h"

#include "game.h"

namespace artifact
{
    TeleporterFeature::TeleporterFeature(PlayableStage *owner, const Vector2 position, const Vector2 destination_position, const Stages destination_stage) :
        destination_stage(destination_stage), destination_position(destination_position), position(position), owner(owner)
    {
        sheet = new SpriteSheet("game/texture/features/teleporter_%d.png", 9, 13);
        this->position = {position.x, position.y + 12};
        owner->register_collider(
                this->position.x + 22,
                this->position.y - 44,
                1,
                88,
                [destination_stage, destination_position](Entity *entity)
                {
                    if (auto *player = dynamic_cast<PlayerEntity *>(entity))
                    {
                        if (destination_stage != Stages::NONE)
                            Game::get_instance()->get_stage_manager()->load_stage(destination_stage, destination_position);
                        else
                        {
                            player->set_position(destination_position.x, destination_position.y);
                        }
                    }
                });
    }
    void TeleporterFeature::draw() const
    {
        if (sheet)
            sheet->draw(position, 2.2);
    }
    void TeleporterFeature::update(const float delta_time)
    {
        if (sheet)
            sheet->update(delta_time);
    }
} // namespace artifact
