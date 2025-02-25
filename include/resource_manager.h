#pragma once
#include <string>

#include "resource.h"

namespace artifact
{
    class ResourceManager
    {
    public:
        static Resource getResource(const char *identifier, const ResourceType &type);
        static Resource getTexture(const char *identifier);
        static Resource getJson(const char *identifier);
        static Resource getText(const char *identifier);
        static Resource getBinary(const char *identifier);
        static ResourceType getType(const std::string &path);
    };
} // namespace artifact
