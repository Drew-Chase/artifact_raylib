
#include "settings/display_settings.h"
#include <filesystem>
#include "nlohmann/json.hpp"
#include "ui/menus/settings_screen.h"

using namespace nlohmann;
using namespace std::filesystem;

namespace artifact
{
    DisplaySettings::DisplaySettings() : SettingsBase("display.json") { DisplaySettings::load(); }
    DisplaySettings::~DisplaySettings() { DisplaySettings::save(); }
    void DisplaySettings::load()
    {
        if (!exists(get_settings_file()))
        {
            reset();
            return;
        }
        std::fstream file = open_settings_file(std::ios::in);
        const json settings = json::parse(file);

        window_mode = settings["window_mode"];
        screen_width = settings.value("screen_width", screen_width);
        screen_height = settings.value("screen_height", screen_height);
        frame_rate = settings.value("frame_rate", frame_rate);
        vsync = settings.value("vsync", vsync);

        file.close();
    }
    void DisplaySettings::save()
    {
        std::fstream file = open_settings_file(std::ios::out);
        json settings;

        settings["window_mode"] = window_mode;
        settings["screen_width"] = screen_width;
        settings["screen_height"] = screen_height;
        settings["frame_rate"] = frame_rate;
        settings["vsync"] = vsync;

        file << settings.dump(4);
        file.flush();
        file.close();
    }
    void DisplaySettings::apply()
    {
        if (!IsWindowReady())
        {
            return;
        }

        const int monitor = GetCurrentMonitor();
        const int monitor_width = GetMonitorWidth(monitor);
        const int monitor_height = GetMonitorHeight(monitor);
        SetTargetFPS(frame_rate);
        if (vsync)
            SetWindowState(FLAG_VSYNC_HINT);
        else
            ClearWindowState(FLAG_VSYNC_HINT);
        if (IsWindowState(FLAG_WINDOW_UNDECORATED))
            ClearWindowState(FLAG_WINDOW_UNDECORATED);

        if (window_mode == WindowMode::WINDOWED || window_mode == WindowMode::WINDOWED_FULLSCREEN)
        {
            if (IsWindowFullscreen())
                ToggleFullscreen();
            if (window_mode == WindowMode::WINDOWED)
            {
                SetWindowSize(screen_width, screen_height);
                const int x = monitor_width / 2 - screen_width / 2;
                const int y = monitor_height / 2 - screen_height / 2;
                TraceLog(LOG_INFO, "Windowed mode: w=%d,h=%d,x=%d,y=%d", monitor_width, monitor_height, x, y);
                SetWindowPosition(x, y);
            } else
            {
                SetWindowState(FLAG_WINDOW_UNDECORATED);
                SetWindowSize(GetScreenWidth(), GetScreenHeight());
            }
        } else if (window_mode == WindowMode::FULLSCREEN)
        {
            SetWindowSize(screen_width, screen_height);
            if (!IsWindowFullscreen())
                ToggleFullscreen();
        }
    }
    void DisplaySettings::reset()
    {
        if (!IsWindowReady())
        {
            return;
        }
        const int monitor = GetCurrentMonitor();
        this->window_mode = WindowMode::FULLSCREEN;
        this->screen_width = GetMonitorWidth(monitor);
        this->screen_height = GetMonitorHeight(monitor);
        this->frame_rate = 60;
        this->vsync = true;
        save();
    }
} // namespace artifact
