
#include "stages/level_1_b_stage.h"

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
        nextlvl_teleporter = new TeleporterFeature(this, {9123.4, -7}, {0, 140});
        secret_teleporter = new TeleporterFeature(this, {-982.2, -153}, {0, 140});

        // Initialize Textures
        set_background("game/texture/stages/level_1b/background.png");

        // Create Colliders
        constexpr float block_scale = 32 * 2.3;
        constexpr float base_x = -64;
        constexpr float base_y = -1790;

        // Ground
        colliders.emplace_back(base_x, base_y, block_scale * 7, block_scale, true);

        // Roof
        colliders.emplace_back(base_x - block_scale, base_y - 4 * block_scale, block_scale * 10, block_scale, true);

        // Walls
        colliders.emplace_back(base_x - block_scale, base_y - 3 * block_scale, block_scale, block_scale * 3, true);

        // Killnet
        // colliders.emplace_back(-500, 500, block_scale * 150, block_scale, [&]
        //                        { player->kill(); });
    }
    Vector2 Level1BStage::get_spawn_position() const { return {0, -1800}; }
    void Level1BStage::spawn_entities()
    {
        entities.erase(std::ranges::remove_if(entities, [this](const Entity *entity)
                                              { return entity != player; })
                               .begin(),
                       entities.end());


        // Spawn enemies
    }
    void Level1BStage::draw() const
    {
        if (is_being_destroyed)
            return;
        BeginMode2D(camera);
        PlayableStage::draw();
        if (nextlvl_teleporter)
            nextlvl_teleporter->draw();
        if (secret_teleporter)
            secret_teleporter->draw();
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
        if (secret_teleporter)
            secret_teleporter->update(delta_time);

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
        if (secret_teleporter)
        {
            delete secret_teleporter;
            secret_teleporter = nullptr;
        }

        UnloadMusicStream(music);
    }
} // namespace artifact
