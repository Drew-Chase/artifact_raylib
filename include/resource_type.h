#pragma once
#include <format>

namespace artifact
{
    enum class ResourceType
    {
        TEXTURE,
        JSON,
        TEXT,
        BINARY,
    };
}

template<>
struct std::formatter<artifact::ResourceType> : std::formatter<std::string_view>
{
    auto format(const artifact::ResourceType type, std::format_context &ctx) const
    {
        std::string_view name;
        switch (type)
        {
            case artifact::ResourceType::TEXTURE:
                name = "texture";
                break;
            case artifact::ResourceType::JSON:
                name = "json";
                break;
            case artifact::ResourceType::TEXT:
                name = "text";
                break;
            case artifact::ResourceType::BINARY:
                name = "binary";
                break;
        }
        return formatter<std::string_view>::format(name, ctx);
    }
};
