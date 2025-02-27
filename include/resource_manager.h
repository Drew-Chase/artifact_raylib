#pragma once
#include <string>

#include "resource.h"

namespace artifact
{
    class ResourceManager
    {
    public:
        static Resource get_resource(const char *identifier, const ResourceType &type);
        static Resource get_texture(const char *identifier);
        static Resource get_json(const char *identifier);
        static Resource get_text(const char *identifier);
        static Resource get_binary(const char *identifier);
        static ResourceType get_type(const std::string &path);
    };
} // namespace artifact
