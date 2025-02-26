#pragma once
#include <format>
#include <stdexcept>
#include <string>

namespace artifact
{
    class ResourceError final : public std::runtime_error
    {
    public:
        explicit ResourceError(const std::string &message) : std::runtime_error(message) {}

        template<typename... Args>
        static ResourceError create(const std::format_string<Args...> fmt, Args &&...args)
        {
            return ResourceError(std::format(fmt, std::forward<Args>(args)...));
        }
    };
} // namespace artifact
