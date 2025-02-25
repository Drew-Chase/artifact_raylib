#pragma once

namespace artifact
{
    class Stage
    {
        const char *identifier;

    public:
        explicit Stage(const char *identifier) { this->identifier = identifier; }

        ~Stage() = delete;

        [[nodiscard]] const char *getIdentifier() const { return this->identifier; }
    };
} // namespace artifact
