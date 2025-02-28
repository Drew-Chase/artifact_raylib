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

    Game::Game() { this->manager = new StageManager(); }

    Game::~Game() { delete this->manager; }

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

        const auto game = get_instance(); // Initialize the singleton.
        StageManager *manager = game->get_stage_manager();
        InitWindow(1280, 720, "Artifact: The Journey Unraveled");

        const auto window_icon = LoadImage("game/app-icon.png");
        SetWindowIcon(window_icon);
        SetTargetFPS(60);
        manager->load_stage(TITLE_SCREEN);

        while (!WindowShouldClose())
        {
            const auto stage = manager->getCurrentStage();
            stage->update();
            BeginDrawing();
            ClearBackground(BLACK);
            stage->draw();
            DrawFPS(10, 10);
            EndDrawing();
        }

        manager->getCurrentStage()->destroy();
        UnloadImage(window_icon);
        CloseWindow();
    }

    void Game::register_log_callback(int msgType, const char *message, va_list args)
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
