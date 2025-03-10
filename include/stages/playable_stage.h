#pragma once
#include <memory>
#include <raylib.h>
#include "stage.h"

namespace artifact
{
    class Entity;
    class PlayableStage : public Stage
    {
    protected:
        Texture2D ground;
        std::vector<Entity *> entities;

    public:

        template<typename T>
        requires std::derived_from<T, Entity>
        T* spawn_entity(int x, int y) {
            auto entity = std::make_unique<T>();
            T* raw_ptr = entity.get();
            entity->spawn(x, y, this);
            entities.push_back(std::move(entity));
            return raw_ptr;
        }

        void startup() override;
        void draw() const override;
        void update(float deltaTime) const override;
        void destroy() override;
    };
} // namespace artifact
