#include "ui/components/containers/container_base.h"
#include <ranges>

void artifact::ContainerBase::draw() {}
void artifact::ContainerBase::update(int mouse_x, int mouse_y) {}
void artifact::ContainerBase::add_component(ComponentBase *component) { this->components[component->get_identifier()] = component; }
void artifact::ContainerBase::remove_component(const size_t index)
{
    if (index < this->components.size())
    {
        const auto it = std::next(this->components.begin(), index);
        this->components.erase(it->first);
    }
}
void artifact::ContainerBase::remove_component(const char *identifier) { this->components.erase(identifier); }
void artifact::ContainerBase::remove_component(ComponentBase *component) { this->components.erase(component->get_identifier()); }
std::vector<artifact::ComponentBase *> artifact::ContainerBase::entries()
{
    std::vector<ComponentBase *> components;
    for (const auto component: this->components | std::views::values)
    {
        components.push_back(component);
    }
    return components;
}
void artifact::ContainerBase::destroy()
{
    for (const ComponentBase *component: this->components | std::views::values)
    {
        delete component;
    }
}
