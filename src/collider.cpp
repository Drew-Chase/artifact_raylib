#include "Collider.h"
#include <algorithm>
#include <cmath>
#include <ranges>

namespace artifact
{
    bool Collider::operator==(const Collider &collider) const { return this->bounds.x == collider.bounds.x && this->bounds.y == collider.bounds.y && this->bounds.width == collider.bounds.width && this->bounds.height == collider.bounds.height && this->is_blocking == collider.is_blocking; }
    Collider::Collider() : bounds({0, 0, 0, 0}), is_blocking(false) {}
    Collider::Collider(const Rectangle bounds, const bool is_blocking) : bounds(bounds), is_blocking(is_blocking) {}
    Collider::Collider(const int x, const int y, const int width, const int height) : bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, is_blocking{true} {}
    Collider::Collider(const int x, const int y, const int width, const int height, const bool is_blocking) : bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, is_blocking(is_blocking) {}
    Collider::Collider(const int x, const int y, const int width, const int height, const std::function<void()> &on_overlap) : on_overlap(on_overlap), bounds{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, is_blocking(false) {}
    bool Collider::is_collider_empty(const Collider &collider) { return collider == EMPTY_COLLIDER; }
    bool Collider::is_entity_colliding(const Entity *entity, const std::vector<Collider> &colliders)
    {
        const auto &[x, y, width, height] = entity->get_bounds();
        const Vector2 bottom_left = {x, y};
        const Vector2 bottom_right = {x + width, y};
        const Vector2 top_left = {x, y + height};
        const Vector2 top_right = {x + width, y + height};

        // Colliders
        const Collider collider_bottom_right = get_collider_at(static_cast<int>(bottom_left.x), static_cast<int>(bottom_left.y), colliders);
        const Collider collider_bottom_left = get_collider_at(static_cast<int>(bottom_right.x), static_cast<int>(bottom_right.y), colliders);
        const Collider collider_top_right = get_collider_at(static_cast<int>(top_left.x), static_cast<int>(top_left.y), colliders);
        const Collider collider_top_left = get_collider_at(static_cast<int>(top_right.x), static_cast<int>(top_right.y), colliders);

        return !is_collider_empty(collider_bottom_right) || !is_collider_empty(collider_bottom_left) || !is_collider_empty(collider_top_right) || !is_collider_empty(collider_top_left);
    }

    Collider Collider::get_collider_at(const int x, const int y, const std::vector<Collider> &colliders, const bool blocking_only)
    {
        const std::vector<Collider> close_colliders = get_colliders_closest_to(x, y, colliders, blocking_only);
        if (close_colliders.empty())
        {
            return EMPTY_COLLIDER;
        }
        const auto fx = static_cast<float>(x);
        // ReSharper disable once CppTooWideScopeInitStatement
        const auto fy = static_cast<float>(y);
        if (CheckCollisionRecs(close_colliders[0].bounds, {fx, fy, 1, 1}))
            return close_colliders[0];
        return EMPTY_COLLIDER;
    }

    std::vector<Collider> Collider::get_colliders_closest_to(const int x, const int y, const std::vector<Collider> &colliders, const bool blocking_only)
    {
        const auto fx = static_cast<float>(x);
        const auto fy = static_cast<float>(y);

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
    void Collider::overlap()
    {
        if (on_overlap && overlap_cooldown <= 0)
        {
            on_overlap();
            overlap_cooldown = 60; // ~60 frame cooldown
        } else if (overlap_cooldown > 0)
            overlap_cooldown -= 1;
    }
} // namespace artifact
