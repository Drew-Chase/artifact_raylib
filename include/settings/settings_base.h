#pragma once
#include <filesystem>
#include <fstream>

namespace artifact
{
    class SettingsBase
    {
    protected:
        // Properties
        const char *filename;

        // Functions
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

        std::filesystem::path get_settings_file() const
        {
            const std::filesystem::path path(std::filesystem::current_path() / "settings" / filename);
            return path;
        }


    public:
        explicit SettingsBase(const char *filename) : filename(filename) {}
        virtual ~SettingsBase() = default;
        virtual void load() {}
        virtual void save() {}
        virtual void apply() {}
        virtual void reset() {}
    };
} // namespace artifact
