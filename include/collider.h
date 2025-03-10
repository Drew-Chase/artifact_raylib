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
        static const Collider EMPTY;

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
         * Default constructor for the Collider class.
         *
         * Initializes a new Collider instance with its default state.
         * This constructor does not perform any specific initialization logic,
         * relying on the compiler-generated default behavior.
         */
        Collider() = default;
        /**
         * Constructs a new Collider instance with specified bounds and blocking state.
         *
         * This constructor initializes the Collider using the given rectangular bounds
         * and a flag indicating whether the collider should block other entities.
         *
         * @param bounds The rectangular boundary defining the size and position of the collider.
         * @param is_blocking A boolean flag indicating whether the collider should act as blocking.
         *                    If true, the collider will prevent movement through it.
         * @return A new instance of the Collider with the specified properties.
         */
        Collider(Rectangle bounds, bool is_blocking);
        /**
         * Constructs a collider instance with the specified position and size, and marks it as blocking by default.
         *
         * @param x The x-coordinate of the upper-left corner of the collider's bounds.
         * @param y The y-coordinate of the upper-left corner of the collider's bounds.
         * @param width The width of the collider's bounds.
         * @param height The height of the collider's bounds.
         * @return An instance of Collider initialized with the given bounds and a blocking state.
         */
        Collider(int x, int y, int width, int height);

        /**
         * Constructs a collider instance with specified position, dimensions, and blocking state.
         *
         * This constructor initializes the collider's bounding box and its blocking property based on the
         * given parameters, enabling representation of physical boundaries or areas used in simulations or games.
         *
         * @param x The x-coordinate of the top-left corner of the collider.
         * @param y The y-coordinate of the top-left corner of the collider.
         * @param width The width of the collider's bounding box.
         * @param height The height of the collider's bounding box.
         * @param is_blocking Indicates whether the collider should act as a blocking object.
         *
         * @return A new instance of the Collider class with specified bounds and blocking behavior.
         */
        Collider(int x, int y, int width, int height, bool is_blocking);

        /**
         * Checks whether the given collider is empty by comparing it to the predefined EMPTY.
         *
         * This function determines if the provided collider has no valid bounds or is marked as inactive by
         * checking for equality with the static EMPTY instance.
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

} // namespace artifact
