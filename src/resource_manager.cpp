
#include "../include/resource_manager.h"

#include <algorithm>
#include <filesystem>
#include <format>
#include <string>

#include "errors/resource_error.h"

namespace artifact
{
    Resource ResourceManager::getTexture(const char *identifier) { return getResource(identifier, ResourceType::TEXTURE); }
    Resource ResourceManager::getJson(const char *identifier) { return getResource(identifier, ResourceType::JSON); }
    Resource ResourceManager::getText(const char *identifier) { return getResource(identifier, ResourceType::TEXT); }
    Resource ResourceManager::getBinary(const char *identifier) { return getResource(identifier, ResourceType::BINARY); }
    Resource ResourceManager::getResource(const char *identifier, const ResourceType &type)
    {
        std::string path;
        if (type == ResourceType::TEXTURE)
            path = std::format("{}/{}.png", type, identifier);
        else if (type == ResourceType::JSON)
            path = std::format("{}/{}.json", type, identifier);
        else
            path = std::format("{}/{}", type, identifier);

        if (std::filesystem::exists(path))
        {
            throw ResourceError::create("Resource at path {} does NOT exist!", path);
        }

        return Resource{
                identifier,
                path.c_str(),
                type,
        };
    }
    ResourceType ResourceManager::getType(const std::string &path)
    {
        // Find the last occurrence of '.' to get the extension
        const size_t dotPos = path.rfind('.');
        if (dotPos == std::string_view::npos)
            return ResourceType::BINARY;

        // Get the extension and convert to lowercase for case-insensitive comparison
        std::string ext(path.substr(dotPos + 1));
        std::ranges::transform(ext, ext.begin(), tolower);

        // Match extensions to resource types
        if (ext == "png")
            return ResourceType::TEXTURE;
        if (ext == "json")
            return ResourceType::JSON;
        if (ext == "txt" || ext == "log")
            return ResourceType::TEXT;

        return ResourceType::BINARY; // Default to binary for unknown extensions
    }
} // namespace artifact
