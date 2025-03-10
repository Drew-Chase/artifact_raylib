#pragma once
#include <raylib.h>
#include <vector>
#include "entities/entity.h"

namespace artifact
{
    class Collider
    {
    public:
        /**
         * Represents an empty collider instance with no bounds and marked as non-blocking.
         *
         * This constant is used as a default or placeholder value for colliders. It is defined
         * with zero-sized bounds and a non-blocking state to signify the absence of a valid collider.
         */
        static const Collider EMPTY_COLLIDER;
        /**
         * Represents the rectangular boundaries of the collider, which define its position and size in the game world.
         *
         * This property is used for collision detection and spatial relationships among entities and colliders.
         */
        Rectangle bounds;
        /**
         * Indicates whether the collider is considered blocking.
         *
         * This property determines if the collider obstructs movement or interactions
         * based on its state. Colliders with this property set to true are treated as
         * blocking, while those with it set to false are considered non-blocking.
         */
        bool is_blocking;
        /**
         * Compares the current collider with another collider for equality.
         *
         * This operator checks if the bounds (x, y, width, height) and the
         * `is_blocking` property of the two colliders are identical.
         *
         * @param collider The collider to compare against.
         * @return True if the current collider is equal to the given collider; otherwise, false.
         */
        bool operator==(const Collider &collider) const;
        /**
         * Checks whether the given collider is empty by comparing it to the predefined EMPTY_COLLIDER.
         *
         * This function determines if the provided collider has no valid bounds or is marked as inactive by
         * checking for equality with the static EMPTY_COLLIDER instance.
         *
         * @param collider The collider to check for emptiness.
         * @return True if the collider is empty, false otherwise.
         */
        static bool is_collider_empty(const Collider &collider);

        /**
         * Determines if a given entity is colliding with any of the specified colliders.
         *
         * This function checks whether the bounds of the given entity overlap with any
         * of the colliders in the provided vector. It evaluates collisions based on
         * the corners of the entity's bounds, verifying whether there is any collider
         * present at each corner.
         *
         * @param entity A pointer to the entity to check for collisions.
         * @param colliders A vector of colliders to test against the entity's bounds.
         * @return True if the entity is colliding with any of the colliders, false otherwise.
         */
        static bool is_entity_colliding(const Entity *entity, const std::vector<Collider> &colliders);
        /**
         * Finds and retrieves the collider located at the specified (x, y) coordinates
         * from a vector of colliders. Can optionally filter to only consider blocking colliders.
         *
         * If no collider exists at the given coordinates, a default empty collider is returned.
         *
         * @param x The x-coordinate to check for a collider.
         * @param y The y-coordinate to check for a collider.
         * @param colliders The vector of colliders to search within.
         * @param blocking_only A flag to determine if only blocking colliders should be considered.
         *                       If true, only colliders marked as blocking are eligible for retrieval.
         * @return The collider located at the given (x, y) coordinates, or an empty collider if none is found.
         */
        static Collider get_collider_at(int x, int y, const std::vector<Collider> &colliders, bool blocking_only = true);
        /**
         * Retrieves a sorted vector of colliders based on their distance from the given coordinates.
         *
         * This function calculates the distance of each collider from the specified point (x, y)
         * and returns them in ascending order of distance. Optionally, only blocking colliders
         * can be included in the result if the `blocking_only` flag is set to true.
         *
         * @param x The x-coordinate from which distances are calculated.
         * @param y The y-coordinate from which distances are calculated.
         * @param colliders A vector of colliders to be considered for distance calculation and sorting.
         * @param blocking_only If true, only blocking colliders are included in the result.
         * @return A vector of colliders sorted by ascending distance from the specified coordinates.
         */
        static std::vector<Collider> get_colliders_closest_to(int x, int y, const std::vector<Collider> &colliders, bool blocking_only = true);
        /**
         * Filters and retrieves all colliders from the given vector of colliders that are marked as blocking.
         *
         * This function returns a vector containing only the colliders where the `is_blocking`
         * property is set to true. Non-blocking colliders are excluded from the output.
         *
         * @param colliders A vector of colliders to filter for blocking colliders.
         * @return A vector of colliders that are marked as blocking.
         */
        static std::vector<Collider> get_blocking_colliders(std::vector<Collider> colliders);
    };
    /**
     * A constant representing an uninitialized or empty collider.
     *
     * This collider is characterized by zero-sized dimensions and a non-interactive state.
     * It serves as a default or placeholder value to indicate the lack of a defined collider.
     */
    const Collider Collider::EMPTY_COLLIDER = Collider{Rectangle{0, 0, 0, 0}, false};

} // namespace artifact
