#include "game.h"
#include <raylib.h>
#include <stdexcept>
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace artifact
{
    // Initialize static member
    Game *Game::instance = nullptr;

    Game::Game()
    {
        manager = new StageManager();
        display_settings = new DisplaySettings();
        controls_settings = new ControlsSettings();
    }

    Game::~Game()
    {
        spdlog::shutdown();
        delete display_settings;
        display_settings = nullptr;

        delete controls_settings;
        controls_settings = nullptr;

        delete manager;
        manager = nullptr;

        instance = nullptr;
    }

    Game *Game::get_instance()
    {
        if (instance == nullptr)
        {
            instance = new Game();
        }
        return instance;
    }

    void Game::run()
    {
        if (instance != nullptr)
            throw std::runtime_error("Game::run(): Game instance already exists");

        const auto game = get_instance(); // Initialize the singleton.

        // Setup the async logger
        spdlog::init_thread_pool(8192, 1);
        spdlog::set_pattern("[%H:%M:%S.%f] [%l] [thread %t] %v");
        spdlog::set_level(spdlog::level::trace);

        const auto rotating_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/game.log", 10 * 1024 * 1024, 6, true);
        const auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        std::vector<spdlog::sink_ptr> sinks{rotating_file_sink, stdout_sink};
        const auto logger = std::make_shared<spdlog::async_logger>("game_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        register_logger(logger);
        spdlog::flush_every(std::chrono::seconds(3));

        SetTraceLogCallback(register_log_callback);

        const auto window_icon = LoadImage("game/app-icon.png");
        StageManager *manager = game->get_stage_manager();


        InitWindow(0, 0, "Artifact: The Journey Unraveled");
        InitAudioDevice();

        // Load Settings
        game->display_settings->load();
        game->controls_settings->load();
        // Apply Settings
        game->display_settings->apply();

        SetWindowIcon(window_icon);
        SetTargetFPS(60);

        manager->load_stage(Stages::LEVEL1A);
        // manager->load_stage(Stages::TITLE_SCREEN);

        instance->isRunning = true;
        while (!WindowShouldClose() && instance->isRunning)
        {
            float deltaTime = GetFrameTime();
            if (constexpr float MAX_DELTA_TIME = 0.05f; deltaTime > MAX_DELTA_TIME)
                deltaTime = MAX_DELTA_TIME;


            const auto stage = manager->get_current_stage();
            stage->update(deltaTime);
            BeginDrawing();
            ClearBackground(BLACK);
            stage->draw();
            DrawFPS(10, 10);
            EndDrawing();
        }

        manager->get_current_stage()->destroy();
        UnloadImage(window_icon);
        CloseAudioDevice();
        CloseWindow();

        // Call the deconstructor.
        delete game;
    }

    void Game::register_log_callback(int msgType, const char *message, const va_list args)
    {
        const auto logger = spdlog::get("game_logger");
        char formattedMessage[1024];
        vsnprintf(formattedMessage, sizeof(formattedMessage), message, args);

        switch (msgType)
        {
            case LOG_TRACE:
                logger->trace(formattedMessage);
                break;
            case LOG_DEBUG:
                logger->debug(formattedMessage);
                break;
            case LOG_INFO:
                logger->info(formattedMessage);
                break;
            case LOG_WARNING:
                logger->warn(formattedMessage);
                break;
            case LOG_ERROR:
                logger->error(formattedMessage);
                break;
            case LOG_FATAL:
                logger->critical(formattedMessage);
                break;
            default:
                logger->info("Unknown log type: {}", msgType);
                break;
        }
        logger->flush(); // Explicit flush after each message
    }

} // namespace artifact
