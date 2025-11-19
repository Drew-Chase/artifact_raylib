
#include "features/teleporter_feature.h"

#include "game.h"

namespace artifact
{
    TeleporterFeature::TeleporterFeature(PlayableStage *owner, const Vector2 position, const Vector2 destination_position, const Stages destination_stage) :
        destination_stage(destination_stage), destination_position(destination_position), position(position), owner(owner)
    {
        sheet = new SpriteSheet("game/texture/features/teleporter_%d.png", 9, 13);
        teleport_sfx = LoadMusicStream("game/audio/sfx/teleport.ogg");
        teleport_sfx.looping = true;
        this->position = {position.x, position.y + 12};
        owner->register_collider(
                this->position.x + 22,
                this->position.y - 44,
                1,
                88,
                [&](Entity *entity)
                {
                    if (auto *player = dynamic_cast<PlayerEntity *>(entity))
                    {
                        captured_player = player;
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
        // the number of seconds that the teleportation should last
        if (sheet)
            sheet->update(delta_time);
        if (captured_player)
        {
            if (timer == 0)
                PlayMusicStream(teleport_sfx);
            UpdateMusicStream(teleport_sfx);
            timer += delta_time;
            if (timer >= .05f)
            {
                captured_player->set_teleporting(true);
            }
            if (timer >= 1.5f && owner && owner->level_open_overlay && !owner->level_open_overlay->is_reversed)
            {
                owner->level_open_overlay->is_reversed = true;
                owner->level_open_overlay->restart();
                StopMusicStream(teleport_sfx);
            }
            if (constexpr float teleport_time = 3.f; timer >= teleport_time)
            {
                timer = 0;
                if (owner && owner->level_open_overlay)
                {
                    owner->level_open_overlay->is_reversed = false;
                    owner->level_open_overlay->reset();
                }
                captured_player->set_teleporting(false);
                if (destination_stage != Stages::NONE)
                    Game::get_instance()->get_stage_manager()->request_stage_change(destination_stage, destination_position);
                else
                    captured_player->set_position(destination_position.x, destination_position.y);
                captured_player = nullptr;
            }
        }
    }
} // namespace artifact
