
#include "settings/controls_settings.h"
#include <nlohmann/json.hpp>
#include <raylib.h>

using namespace nlohmann;

namespace artifact
{
    ControlsSettings::ControlsSettings() : SettingsBase("keybindings.json") {}
    void ControlsSettings::load()
    {
        if (!exists(get_settings_file()))
        {
            reset();
            return;
        }

        std::fstream file = open_settings_file(std::ios::in);
        const json settings = json::parse(file);

        movement_jump = settings.value("movement_jump", movement_jump);
        movement_left = settings.value("movement_left", movement_left);
        movement_right = settings.value("movement_right", movement_right);
        movement_sprint = settings.value("movement_sprint", movement_sprint);
        combat_light = settings.value("combat_light", combat_light);
        combat_dash = settings.value("combat_dash", combat_dash);
        menu_pause = settings.value("menu_pause", menu_pause);
        toggle_sprint = settings.value("toggle_sprint", toggle_sprint);

        file.close();
    }
    void ControlsSettings::save()
    {
        std::fstream file = open_settings_file(std::ios::out);
        json settings;
        settings["movement_jump"] = movement_jump;
        settings["movement_left"] = movement_left;
        settings["movement_right"] = movement_right;
        settings["movement_sprint"] = movement_sprint;
        settings["combat_light"] = combat_light;
        settings["combat_dash"] = combat_dash;
        settings["menu_pause"] = menu_pause;
        settings["toggle_sprint"] = toggle_sprint;
        file << settings.dump(4);
        file.flush();
        file.close();
    }
    void ControlsSettings::reset()
    {
        movement_jump = KEY_SPACE;
        movement_left = KEY_A;
        movement_right = KEY_D;
        movement_sprint = KEY_LEFT_SHIFT;
        combat_light = MOUSE_BUTTON_RIGHT;
        combat_dash = MOUSE_BUTTON_LEFT;
        menu_pause = KEY_ESCAPE;
        toggle_sprint = false;

        save();
    }
    bool ControlsSettings::pressed(const int key)
    {
        if (key <= 6)
            return IsMouseButtonPressed(key);
        return IsKeyPressed(key);
    }
    bool ControlsSettings::down(const int key)
    {
        if (key <= 6)
            return IsMouseButtonDown(key);
        return IsKeyDown(key);
    }
    bool ControlsSettings::up(const int key)
    {
        if (key <= 6)
            return IsMouseButtonUp(key);
        return IsKeyUp(key);
    }
} // namespace artifact
