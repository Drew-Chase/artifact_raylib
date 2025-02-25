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

    Game *Game::getInstance()
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
        // spdlog::init_thread_pool(8192, 1);
        // spdlog::set_pattern("[%H:%M:%S.%f] [%L] [thread %t] %v");
        spdlog::set_level(spdlog::level::debug);
        // const auto rotating_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/game.log", 10 * 1024 * 1024, 6, true);
        // const auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        // std::vector<spdlog::sink_ptr> sinks{rotating_file_sink, stdout_sink};
        // const auto logger = std::make_shared<spdlog::async_logger>("game_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        // register_logger(logger);
        // spdlog::flush_every(std::chrono::seconds(3));
        // SetTraceLogCallback(SpdLoggerCallback);


        const auto game = getInstance(); // Initialize the singleton.
        StageManager *manager = game->getManager();
        InitWindow(800, 450, "raylib [core] example - basic window");
        manager->loadStage(Stage::TITLE_SCREEN);

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

        CloseWindow();
    }

    // void Game::SpdLoggerCallback(int msgType, const char *message, va_list args)
    // {
    //     char formattedMessage[1024];
    //     vsnprintf(formattedMessage, sizeof(formattedMessage), message, args);
    //
    //     switch (msgType)
    //     {
    //         case LOG_TRACE:
    //             spdlog::trace(formattedMessage);
    //             break;
    //         case LOG_DEBUG:
    //             spdlog::debug(formattedMessage);
    //             break;
    //         case LOG_INFO:
    //             spdlog::info(formattedMessage);
    //             break;
    //         case LOG_WARNING:
    //             spdlog::warn(formattedMessage);
    //             break;
    //         case LOG_ERROR:
    //             spdlog::error(formattedMessage);
    //             break;
    //         case LOG_FATAL:
    //             spdlog::critical(formattedMessage);
    //             break;
    //         default:
    //             spdlog::info("Unknown log type: {}", msgType);
    //             break;
    //     }
    // }

} // namespace artifact
