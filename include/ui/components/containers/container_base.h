#pragma once
#include <map>
#include <string>
#include <vector>

#include "ui/components/component_base.h"

namespace artifact
{
    class ContainerBase : public ComponentBase
    {
        std::map<std::string, ComponentBase *> components;

    public:
        explicit ContainerBase(const char *identifier, Stage *owner) : ComponentBase(identifier, owner) {}
        virtual ~ContainerBase();
        void draw() override;
        void update(int mouse_x, int mouse_y) override;
        virtual void add_component(ComponentBase *component);

        template<typename T, typename... Args>
        T* add_component(const char* identifier, Args&&... args) {
            T* component = new T(identifier, std::forward<Args>(args)...);
            this->components[component->get_identifier()] = component;
            return component;
        }

        virtual void remove_component(size_t index);
        virtual void remove_component(const char *identifier);
        virtual void remove_component(ComponentBase *component);
        virtual std::vector<ComponentBase *> entries();
        virtual void destroy();
    };
} // namespace artifact
