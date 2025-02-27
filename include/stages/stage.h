#pragma once

namespace artifact
{
    class Stage
    {
        const char *identifier;

    public:
        explicit Stage(const char *identifier) : identifier(identifier) {}

        virtual ~Stage() = default;

        virtual void draw() const { draw(false); }
        virtual void draw(bool first_draw) const {}
        virtual void update() const { update(false); }
        virtual void update(bool first_update) const {}
        virtual void startup() {}
        virtual void destroy() {}

        [[nodiscard]] const char *get_identifier() const { return this->identifier; }
    };
} // namespace artifact
