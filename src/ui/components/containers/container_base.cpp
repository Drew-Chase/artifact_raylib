#include "ui/components/containers/container_base.h"
#include <cstring>
#include <ranges>
#include <string>

void artifact::ContainerBase::draw() {}

void artifact::ContainerBase::update(int mouse_x, int mouse_y) {}

void artifact::ContainerBase::add_component(ComponentBase *component) { this->components.push_back(std::unique_ptr<ComponentBase>(component)); }

void artifact::ContainerBase::remove_component(const size_t index)
{
    if (index < this->components.size())
    {
        const auto it = std::next(this->components.begin(), index);
        this->components.erase(it);
    }
}

void artifact::ContainerBase::remove_component(const char *identifier)
{

    if (const auto it = std::ranges::find_if(components, [identifier](const std::unique_ptr<ComponentBase> &component) { return std::strcmp(component->get_identifier(), identifier) == 0; }); it != components.end())
    {
        components.erase(it);
    }
}

void artifact::ContainerBase::remove_component(ComponentBase *component)
{
    if (const auto it = std::ranges::find_if(components, [component](const std::unique_ptr<ComponentBase> &comp) { return comp.get() == component; }); it != components.end())
    {
        components.erase(it);
    }
}


void artifact::ContainerBase::destroy() { components.clear(); }
