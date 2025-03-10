#include "Collider.h"
#include <algorithm>
#include <cmath>
#include <ranges>

namespace artifact
{
    bool Collider::operator==(const Collider &collider) const { return this->bounds.x == collider.bounds.x && this->bounds.y == collider.bounds.y && this->bounds.width == collider.bounds.width && this->bounds.height == collider.bounds.height && this->is_blocking == collider.is_blocking; }
    Collider::Collider(const Rectangle bounds, const bool is_blocking) : bounds(bounds), is_blocking(is_blocking) {}
    Collider::Collider(const int x, const int y, const int width, const int height) : bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, is_blocking{true} {}
    Collider::Collider(const int x, const int y, const int width, const int height, const bool is_blocking) : bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, is_blocking(is_blocking) {}
    bool Collider::is_collider_empty(const Collider &collider) { return collider == EMPTY; }
    bool Collider::is_entity_colliding(const Entity *entity, const std::vector<Collider> &colliders)
    {
        const auto &[x, y, width, height] = entity->get_bounds();
        const Vector2 bottom_left = {x, y};
        const Vector2 bottom_right = {x + width, y};
        const Vector2 top_left = {x, y + height};
        const Vector2 top_right = {x + width, y + height};

        // Colliders
        const Collider collider_bottom_right = get_collider_at(bottom_left.x, bottom_left.y, colliders);
        const Collider collider_bottom_left = get_collider_at(bottom_right.x, bottom_right.y, colliders);
        const Collider collider_top_right = get_collider_at(top_left.x, top_left.y, colliders);
        const Collider collider_top_left = get_collider_at(top_right.x, top_right.y, colliders);

        return !is_collider_empty(collider_bottom_right) || !is_collider_empty(collider_bottom_left) || !is_collider_empty(collider_top_right) || !is_collider_empty(collider_top_left);
    }

    Collider Collider::get_collider_at(const int x, const int y, const std::vector<Collider> &colliders, const bool blocking_only)
    {
        const std::vector<Collider> close_colliders = get_colliders_closest_to(x, y, colliders, blocking_only);
        if (close_colliders.empty())
        {
            return EMPTY;
        }
        const float fx = static_cast<float>(x);
        const float fy = static_cast<float>(y);
        if (CheckCollisionRecs(close_colliders[0].bounds, {fx, fy, 1, 1}))
            return close_colliders[0];
        return EMPTY;
    }

    std::vector<Collider> Collider::get_colliders_closest_to(const int x, const int y, const std::vector<Collider> &colliders, const bool blocking_only)
    {
        const float fx = static_cast<float>(x);
        const float fy = static_cast<float>(y);

        std::vector<Collider> filtered_colliders = blocking_only ? get_blocking_colliders(colliders) : colliders;

        std::ranges::sort(filtered_colliders,
                          [fx, fy](const Collider &a, const Collider &b)
                          {
                              const float distance_a = std::hypot(a.bounds.x - fx, a.bounds.y - fy);
                              const float distance_b = std::hypot(b.bounds.x - fx, b.bounds.y - fy);
                              return distance_a < distance_b;
                          });
        return filtered_colliders;
    }

    std::vector<Collider> Collider::get_blocking_colliders(std::vector<Collider> colliders)
    {
        std::vector<Collider> blocking_colliders;
        auto filtered_view = colliders | std::views::filter([](const Collider &collider) { return collider.is_blocking; });
        std::ranges::copy(filtered_view, std::back_inserter(blocking_colliders));
        return blocking_colliders;
    }
} // namespace artifact
