
#include "stages/level_1_b_stage.h"

#include "entities/demon_bat_entity.h"
#include "entities/roamer_entity.h"

namespace artifact
{
    Level1BStage::Level1BStage() :
        PlayableStage("level_1b") {}
    void Level1BStage::startup()
    {
        PlayableStage::startup();
        music = LoadMusicStream("game/audio/music/level1v2.ogg");
        music.looping = true;
        SetMusicVolume(music, 0.15f);
        PlayMusicStream(music);

        const auto [x, y] = get_spawn_position();
        this->player = spawn_entity<PlayerEntity>(x, y);

        // Setup features
        nextlvl_teleporter = new TeleporterFeature(this, {6539.3, -676}, Stages::LEVEL1C);

        // Initialize Textures
        set_background("game/texture/stages/level_1b/background.png");

        // Create Colliders
        constexpr float block_scale = 32 * 2.3;
        float base_x = -62;
        float base_y = -1790;

        // Ground
        colliders.emplace_back(base_x, base_y, block_scale * 7, block_scale, true);
        base_y += block_scale;
        base_x += block_scale * 7;
        colliders.emplace_back(base_x, base_y, block_scale * 9, block_scale, true);
        base_x += block_scale * 9;
        base_y -= block_scale;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale, true);
        base_x += block_scale;
        base_y -= block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale * 4, true);
        base_x += block_scale * 2;
        base_y += block_scale * 2;
        colliders.emplace_back(base_x, base_y, block_scale * 3, block_scale, true);
        base_x += block_scale * 5;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale * 4, true);
        base_x -= block_scale * 2;
        base_y += block_scale * 3;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale, true);
        base_x -= block_scale * 4;
        base_y += block_scale * 2;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale, true);
        base_x += block_scale;
        base_y += block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 9, block_scale, true);
        base_x += block_scale * 9;
        base_y -= block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale, true);
        base_x += block_scale * 2;
        base_y += block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale, true);
        base_x += block_scale * 2;
        base_y -= block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale, true);
        base_x += block_scale * 2;
        base_y += block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale, true);
        base_x += block_scale * 2;
        base_y -= block_scale * 3;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale * 3, true);
        base_x += block_scale * 2;
        base_y -= block_scale * 3;
        colliders.emplace_back(base_x, base_y, block_scale * 11, block_scale * 23, true);
        base_x += block_scale * 13;
        colliders.emplace_back(base_x, base_y, block_scale * 17, block_scale * 18, true);
        base_x -= block_scale * 2;
        base_y += block_scale * 22;
        colliders.emplace_back(base_x, base_y, block_scale * 12, block_scale * 6, true);
        base_x += block_scale * 16;
        base_y -= block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 7, block_scale * 6, true);
        base_x += block_scale * 7;
        base_y -= block_scale * 2;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale * 2, true);
        base_x += block_scale * 2;
        base_y -= block_scale * 2;
        colliders.emplace_back(base_x, base_y, block_scale * 2, block_scale * 2, true);
        base_x += block_scale * 2;
        base_y -= block_scale * 2;
        colliders.emplace_back(base_x, base_y, block_scale * 16, block_scale * 2, true);

        // Roof
        base_x = -62;
        base_y = -1790;

        base_y -= 4 * block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 9, block_scale, true);
        base_y += block_scale;
        base_x += block_scale * 9;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale, true);
        base_y += block_scale;
        base_x += block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 4, block_scale, true);
        base_y -= block_scale;
        base_x += block_scale * 4;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale, true);
        base_y -= block_scale;
        base_x += block_scale;
        colliders.emplace_back(base_x, base_y, block_scale * 10, block_scale, true);
        base_y += block_scale;
        base_x += block_scale * 11;
        colliders.emplace_back(base_x, base_y, block_scale * 28, block_scale, true);
        base_y += block_scale * 22;
        base_x += block_scale * 39;
        colliders.emplace_back(base_x, base_y, block_scale * 3, block_scale, true);

        // Walls
        base_x = -62 - block_scale;
        base_y = -1790 - 3 * block_scale;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale * 3, true);
        base_x += block_scale * 18;
        base_y += block_scale * 6;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale * 3, true);
        base_x += block_scale * 8;
        base_y -= block_scale * 6;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale * 4, true);
        base_x += block_scale * 29;
        base_y += block_scale;
        colliders.emplace_back(base_x, base_y, block_scale, block_scale * 3, true);
        colliders.emplace_back(6705, -6760, block_scale, block_scale * 9, true);

        // Killnet
        colliders.emplace_back(4350, block_scale * 4, block_scale * 6, block_scale, [&]
                               { player->kill(); });
    }
    Vector2 Level1BStage::get_spawn_position() const { return {0, -1800}; }
    void Level1BStage::spawn_entities()
    {
        entities.erase(std::ranges::remove_if(entities, [this](const Entity *entity)
                                              { return entity != player; })
                               .begin(),
                       entities.end());


        // Spawn enemies
        spawn_entity<RoamerEntity>(457, -1748, Vector2{457, -1780}, Vector2{1051, -1780});
        spawn_entity<RoamerEntity>(544, -1748, Vector2{457, -1780}, Vector2{1051, -1780});
        spawn_entity<RoamerEntity>(634, -1748, Vector2{457, -1780}, Vector2{1051, -1780});

        spawn_entity<DemonBatEntity>(1237, -1927);

        spawn_entity<RoamerEntity>(1335, -1748, Vector2{1335, -1780}, Vector2{1492, -1780});

        spawn_entity<RoamerEntity>(1330, -1306, Vector2{1334, -1338}, Vector2{1934, -1338});
        spawn_entity<RoamerEntity>(1394, -1306, Vector2{1334, -1338}, Vector2{1934, -1338});
        spawn_entity<RoamerEntity>(1458, -1306, Vector2{1334, -1338}, Vector2{1934, -1338});
        spawn_entity<RoamerEntity>(1522, -1306, Vector2{1334, -1338}, Vector2{1934, -1338});

        spawn_entity<DemonBatEntity>(2037, -1412);
        spawn_entity<DemonBatEntity>(2333, -1412);

        spawn_entity<RoamerEntity>(2730, -1748, Vector2{2732, -1780}, Vector2{3478, -1780});
        spawn_entity<RoamerEntity>(2794, -1748, Vector2{2732, -1780}, Vector2{3478, -1780});
        spawn_entity<RoamerEntity>(2858, -1748, Vector2{2732, -1780}, Vector2{3478, -1780});
        spawn_entity<RoamerEntity>(2922, -1748, Vector2{2732, -1780}, Vector2{3478, -1780});

        spawn_entity<RoamerEntity>(3542, -132, Vector2{3542, -161}, Vector2{4360, -161});
        spawn_entity<RoamerEntity>(3642, -132, Vector2{3542, -161}, Vector2{4360, -161});
        spawn_entity<RoamerEntity>(3742, -132, Vector2{3542, -161}, Vector2{4360, -161});
        spawn_entity<RoamerEntity>(3842, -132, Vector2{3542, -161}, Vector2{4360, -161});
        spawn_entity<RoamerEntity>(3842, -132, Vector2{3542, -161}, Vector2{4360, -161});

        spawn_entity<RoamerEntity>(5534, -644, Vector2{5534, -676}, Vector2{6641, -676});
        spawn_entity<RoamerEntity>(5634, -644, Vector2{5534, -676}, Vector2{6641, -676});
        spawn_entity<RoamerEntity>(5734, -644, Vector2{5534, -676}, Vector2{6641, -676});
        spawn_entity<RoamerEntity>(5834, -644, Vector2{5534, -676}, Vector2{6641, -676});
    }
    void Level1BStage::draw() const
    {
        if (is_being_destroyed)
            return;
        BeginMode2D(camera);
        PlayableStage::draw();
        if (nextlvl_teleporter)
            nextlvl_teleporter->draw();
        EndMode2D();
        PlayableStage::draw_ui();
    }
    void Level1BStage::update(const float delta_time)
    {
        if (is_being_destroyed)
            return;
        PlayableStage::update(delta_time);
        if (nextlvl_teleporter)
            nextlvl_teleporter->update(delta_time);

        if (music.stream.buffer)
            UpdateMusicStream(music);
    }
    void Level1BStage::destroy()
    {
        if (is_being_destroyed)
            return;
        PlayableStage::destroy();
        if (nextlvl_teleporter)
        {
            delete nextlvl_teleporter;
            nextlvl_teleporter = nullptr;
        }

        UnloadMusicStream(music);
    }
} // namespace artifact
