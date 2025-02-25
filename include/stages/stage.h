#pragma once

namespace artifact
{
    class Stage
    {
        const char *identifier;

    public:
        static constexpr const char *TITLE_SCREEN = "title_screen";


        explicit Stage(const char *identifier) : identifier(identifier) {}

        ~Stage() = default;
        void draw() const { draw(false); }
        void draw(bool first_draw) const;
        void update() const { update(false); }
        void update(bool first_update) const;

        [[nodiscard]] const char *getIdentifier() const { return this->identifier; }
    };
} // namespace artifact
