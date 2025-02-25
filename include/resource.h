#pragma once
#include "resource_type.h"

namespace artifact
{
    struct Resource
    {
        const char *name;
        const char *path;
        ResourceType type;
    };
} // namespace artifact
