#pragma once
#include <filesystem>
#include <fstream>

namespace artifact
{
    /**
     * A base class for managing settings stored in a file.
     *
     * This class provides functionality for associating a settings file,
     * interacting with file paths, and virtual methods to be overridden
     * for specific settings-related operations such as loading, saving,
     * applying, and resetting configurations.
     */
    class SettingsBase
    {
    protected:
        /**
         * A pointer to a C-style string representing the name or path of a file.
         *
         * This variable is used to associate a specific file with the settings or configurations
         * managed by the enclosing class.
         */
        const char *filename;

        /**
         * Opens the settings file in the specified mode.
         *
         * This method attempts to open the settings file defined by the settings file path.
         * If the parent directory of the file path does not exist, it creates the necessary directories.
         * An exception is thrown if the file cannot be opened.
         *
         * @param open_mode The mode in which the settings file should be opened (e.g., read, write, append).
         * @return A std::fstream object associated with the opened settings file.
         * @throws std::runtime_error If the file could not be opened.
         */
        std::fstream open_settings_file(const std::ios::openmode open_mode) const
        {
            const std::filesystem::path path = get_settings_file();
            if (path.has_parent_path())
                create_directories(path.parent_path());

            std::fstream file(path, open_mode);
            if (!file.is_open())
                throw std::runtime_error("Could not open settings file");
            return file;
        }

        /**
         * Retrieves the path to the settings file.
         *
         * This method constructs the full path to the settings file by appending the
         * "settings" directory and the filename to the current working directory.
         *
         * @return The full path to the settings file as a std::filesystem::path object.
         */
        std::filesystem::path get_settings_file() const
        {
            const std::filesystem::path path(std::filesystem::current_path() / "settings" / filename);
            return path;
        }


    public:
        /**
         * Constructs a SettingsBase object with the given filename.
         *
         * @param filename The name of the file associated with the settings.
         */
        explicit SettingsBase(const char *filename) : filename(filename) {}
        /**
         * @brief Virtual destructor for the SettingsBase class.
         *
         * This ensures proper cleanup of resources in derived classes when the
         * object is deleted via a pointer to the base class.
         */
        virtual ~SettingsBase() = default;
        /**
         * @brief Loads settings from the associated file.
         *
         * This method should be overridden to define the logic for loading
         * settings from the settings file. The derived class should use this
         * method to configure its properties based on the data read from the file.
         *
         * @note Implementations may throw exceptions if the file cannot be
         *       opened or if there are issues reading the data.
         *
         * @see artifact::SettingsBase::open_settings_file()
         * @see artifact::SettingsBase::get_settings_file()
         */
        virtual void load() {}
        /**
         * @brief Saves the current settings to a persistent storage medium.
         *
         * This method is intended to be overridden in derived classes to implement
         * custom behavior for saving configuration or settings data. By default,
         * this function performs no operation.
         *
         * Derived classes should ensure that data is written in a suitable format
         * and handle any necessary file or storage operations to persist the settings.
         * This may involve interacting with files, databases, or other storage mechanisms.
         *
         * @note It is the responsibility of the derived class to handle errors and
         * exceptions appropriately during the save operation to ensure proper operation.
         */
        virtual void save() {}
        /**
         * @brief Virtual method intended to apply settings or configurations.
         *
         * This method is called to apply changes or initialize setups based on the current settings.
         * It is designed to be overridden by derived classes to provide specific behaviors for
         * applying changes or adjustments to the settings.
         *
         * By default, the method does nothing. Subclasses are expected to implement
         * functionality as required for their specific use case.
         */
        virtual void apply() {}
        /**
         * @brief Resets the settings to their default state.
         *
         * This method is intended to be overridden by derived classes to implement
         * specific behavior for resetting settings. By default, this method does nothing.
         */
        virtual void reset() {}
    };
} // namespace artifact
