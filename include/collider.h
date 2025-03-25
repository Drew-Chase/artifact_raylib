#pragma once
#include <functional>
#include <raylib.h>
#include <vector>

namespace artifact
{
    class Entity;
    class Collider
    {
        std::function<void()> on_overlap;
        std::function<void(Entity *)> on_entity_overlap;

        int overlap_cooldown = 0;
        Entity *overlapping_entity = nullptr;
        Entity *owner = nullptr;

    public:
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
        Collider();
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
         * Constructs a Collider with specified position, size, and overlap callback function.
         *
         * This constructor initializes the rectangular boundaries of the collider and sets
         * the callback function to be executed when an overlap event occurs between colliders.
         *
         * @param x The x-coordinate of the collider's position in the game world.
         * @param y The y-coordinate of the collider's position in the game world.
         * @param width The width of the collider.
         * @param height The height of the collider.
         * @param on_overlap A callback function to be triggered when the collider overlaps with another.
         * @return A constructed Collider object.
         */
        Collider(int x, int y, int width, int height, const std::function<void()> &on_overlap);
        /**
         * Constructs a Collider instance with specified position, size, and overlap handling logic.
         *
         * This constructor initializes the collider's position and dimensions in the game world,
         * and sets up a callback to handle interactions with overlapping entities.
         *
         * @param x The x-coordinate of the collider's top-left corner.
         * @param y The y-coordinate of the collider's top-left corner.
         * @param width The width of the collider.
         * @param height The height of the collider.
         * @param on_entity_overlap A callback function triggered when an entity overlaps with this collider.
         */
        Collider(int x, int y, int width, int height, const std::function<void(Entity *)> &on_entity_overlap);


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


        /**
         * This is called when an entity overlaps with a collider instead of colliding with it.
         */
        void overlap();
        /**
         * Handles the overlap event when this collider interacts with the specified entity.
         *
         * This method is responsible for setting the overlapping entity, triggering any associated
         * overlap callbacks, and applying a cooldown to avoid repeated overlap events in quick succession.
         *
         * @param entity A pointer to the Entity instance that this collider overlaps with.
         */
        void overlap(Entity *entity);
        /**
         * Assigns an owner entity to this collider.
         *
         * This method links the collider to a specific entity, establishing ownership and allowing the collider
         * to associate its behavior or properties with the entity it belongs to.
         *
         * @param entity A pointer to the Entity object that will be set as the owner of the collider.
         */
        void set_owner(Entity *entity) { this->owner = entity; }
    };
    static const auto EMPTY_COLLIDER = Collider();
} // namespace artifact
