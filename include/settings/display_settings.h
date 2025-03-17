#pragma once
#include "settings_base.h"

namespace artifact
{
    /**
     * @enum WindowMode
     * @brief Enumerates the different window modes available for the application.
     *
     * WindowMode defines the various display modes that can be used to configure
     * the application's display behavior. These modes dictate how the application
     * renders its window on the screen.
     *
     * Available window modes:
     * - FULLSCREEN: The application runs in fullscreen mode.
     * - WINDOWED: The application runs in a resizable window.
     * - WINDOWED_FULLSCREEN: The application runs in a borderless window, occupying the full screen.
     *
     * This enumeration is primarily used in conjunction with the DisplaySettings class
     * to configure and apply display-related preferences based on user or default settings.
     */
    enum class WindowMode
    {
        /**
         * @brief The application runs in fullscreen mode.
         *
         * In this mode, the application occupies the entire screen, hiding
         * the taskbar and other overlays. It is typically used for immersive
         * experiences such as games or media playback. The resolution matches
         * the user's display settings.
         */
        FULLSCREEN,
        /**
         * @brief The application runs in a resizable window.
         *
         * This mode allows the user to resize the application window, and it
         * does not occupy the full screen. It provides a flexible viewing area
         * and is often used for desktop applications.
         */
        WINDOWED,
        /**
         * @brief The application runs in a borderless fullscreen window.
         *
         * This mode appears similar to fullscreen but retains window behavior,
         * such as quick tabbing between applications. It occupies the entire screen
         * and removes window decorations (e.g., title bar, borders).
         */
        WINDOWED_FULLSCREEN,
    };
    /**
     * @class DisplaySettings
     * @brief Manages the display-related settings of the application.
     *
     * The DisplaySettings class is responsible for storing, managing, and applying
     * configuration properties associated with the application's display, such as
     * screen resolution, frame rate, and window settings. It provides functionality
     * to load and save these settings to a configuration file in addition to modifying
     * runtime behavior through specific methods.
     *
     * The settings controlled by this class include:
     * - Window mode (fullscreen, windowed, borderless fullscreen).
     * - Screen width and height in pixels.
     * - Frame rate for rendering and updates.
     * - Vertical synchronization setting (VSync).
     *
     * The class leverages a configuration file ("display.json") for persistent storage
     * and allows resetting the settings to their default values. It incorporates methods
     * to ensure that runtime application behavior aligns with the specified or default
     * display configurations.
     *
     * This class inherits from SettingsBase and overrides key member functions to provide
     * specialized behavior for managing display settings.
     */
    class DisplaySettings final : public SettingsBase
    {

    public:
        // Display Settings


        /**
         * @brief Represents the desired window mode for the application.
         *
         * The window mode determines how the application's window will be displayed
         * on the screen. It can take one of the following values from the WindowMode
         * enumeration:
         * - FULLSCREEN: The application will run in fullscreen mode, occupying the
         *   entire screen.
         * - WINDOWED: The application will run in a resizable window that does not fully
         *   cover the screen.
         * - WINDOWED_FULLSCREEN: The application will run in fullscreen mode while
         *   still behaving like a window (borderless fullscreen window).
         *
         * This variable is utilized in functions such as load, save, and apply of
         * the DisplaySettings class to load from or save to settings, as well as
         * to apply the display configuration at runtime.
         */
        WindowMode window_mode;
        /**
         * @brief Represents the width of the application window or screen in pixels.
         *
         * This variable is used as part of the display settings to define the width
         * of the window or screen resolution. It is configurable and can be loaded
         * or saved through the display settings system. The value influences the size
         * of the application window when displayed and is applied during runtime to
         * adjust the graphical output.
         *
         * @note The default value may vary and is loaded from or saved to a settings file.
         *
         * @see DisplaySettings::load()
         * @see DisplaySettings::save()
         * @see DisplaySettings::apply()
         */
        unsigned int screen_width;
        /**
         * @brief The height of the application's display screen in pixels.
         *
         * This variable represents the vertical resolution of the application
         * window. It is used to configure and apply display settings, such as
         * initializing the window size, saving and loading user preferences, and
         * applying display configurations. The value is adjustable depending on
         * the user's settings and is usually set during the loading of configuration data.
         */
        unsigned int screen_height;
        /**
         * Represents the target frame rate for rendering and updating the display.
         *
         * This variable determines the number of frames per second (FPS) the application aims to achieve.
         * The frame rate is used to control the rendering frequency and can directly affect the performance
         * and smoothness of the visual output. Typically, higher frame rates result in smoother visuals but
         * may require more processing power, whereas lower frame rates can reduce resource usage but may
         * lead to choppier visuals.
         *
         * The value of `frame_rate` is managed through the DisplaySettings class and can be loaded, saved,
         * applied, or reset via appropriate member functions. It is initially set to a default value when
         * reset (e.g., 60 FPS).
         */
        unsigned int frame_rate;
        /**
         * @brief Indicates whether vertical synchronization (VSync) is enabled or disabled.
         *
         * When enabled (true), VSync synchronizes the application's frame rate with the monitor's refresh rate
         * to prevent screen tearing. When disabled (false), the application runs at its target frame rate without
         * synchronization, potentially increasing performance at the cost of screen tearing.
         *
         * This variable can be loaded from, saved to, and applied through the DisplaySettings class to manage
         * display configurations.
         */
        bool vsync;

        /**
         * @brief Constructs a DisplaySettings object and initializes it with a settings file.
         *
         * This constructor initializes the DisplaySettings object by calling the base
         * class constructor with the path to the "display.json" configuration file.
         * It is used to manage and store the display-related settings for the application.
         *
         * The settings are read from or written to the "display.json" file, encapsulating
         * display configuration details.
         *
         * @return A new instance of the DisplaySettings class with default values loaded
         *         from the associated configuration file.
         */
        explicit DisplaySettings();
        /**
         * @brief Destructor for the DisplaySettings class.
         *
         * Ensures that any pending display configuration settings are saved when
         * an instance of the DisplaySettings class is destroyed. This operation
         * ensures that any runtime modifications to the display settings persist
         * between application sessions.
         *
         * The destructor leverages the save function internally to commit current
         * settings before cleanup.
         */
        ~DisplaySettings() override;
        /**
         * @brief Loads display settings from a configuration file.
         *
         * This method reads the display configuration from a settings file and applies
         * the stored values to the corresponding properties of the DisplaySettings class.
         * If the settings file does not exist, default values are restored using the reset method.
         *
         * The following properties are updated based on the settings file content:
         * - window_mode: The application's display mode (fullscreen, windowed, etc.).
         * - screen_width: The width of the application window or screen.
         * - screen_height: The height of the application window or screen.
         * - frame_rate: The target frame rate for rendering.
         * - vsync: The vertical synchronization setting.
         *
         * If a setting is not explicitly defined in the file, the previous value remains unchanged.
         */
        void load() override;
        /**
         * @brief Saves the current display settings to a configuration file.
         *
         * This method serializes the display settings into a structured JSON format
         * and writes them to a settings file. The saved settings include:
         * - window_mode: The window mode of the application.
         * - screen_width: The width of the display screen in pixels.
         * - screen_height: The height of the display screen in pixels.
         * - frame_rate: The target frame rate for rendering.
         * - vsync: A flag indicating whether vertical synchronization is enabled.
         *
         * The file is opened in output mode, and the serialized settings are written
         * with indentation for readability. After writing, the file is flushed and closed
         * to ensure data integrity.
         */
        void save() override;
        /**
         * @brief Configures and applies the display settings at runtime.
         *
         * This method adjusts the application's display settings based on the current
         * configuration, ensuring the desired screen mode, resolution, and options like
         * V-Sync are applied. The function first checks if the application window is ready
         * before proceeding to apply the settings. It determines the active monitor's
         * resolution and applies the necessary adjustments based on the window mode and
         * frame rate settings. The V-Sync flag is either enabled or disabled, and the
         * application window is positioned or reconfigured based on the selected mode:
         *
         * - FULLSCREEN mode will switch the application to fullscreen if not already set.
         * - WINDOWED mode sets a resizable window centered on the active monitor.
         * - WINDOWED_FULLSCREEN mode activates borderless fullscreen resembling a full
         *   monitor size but without toggling actual fullscreen state.
         *
         * @note The function is designed to maintain window-related state flags consistently
         * based on the specified settings.
         */
        void apply() override;
        /**
         * @brief Resets the display settings to their default configuration.
         *
         * This method restores the display settings to their default values, ensuring
         * a consistent and reliable initial state for the application. Specifically, it:
         * - Sets the window_mode to FULLSCREEN.
         * - Configures the screen_width and screen_height based on the dimensions of
         *   the current monitor.
         * - Sets the frame rate to 60.
         * - Enables vertical synchronization (vsync).
         *
         * The method only performs these actions if the window is ready for
         * initialization. If the window is not in a ready state, the method exits
         * without making any changes. After resetting the values, it invokes the save
         * function to persist the updated settings.
         */
        void reset() override;
    };
} // namespace artifact
