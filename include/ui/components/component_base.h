#pragma once
#include <raylib.h>

#include "stages/stage.h"

namespace artifact
{
    class ComponentBase
    {

    protected:
        const char *identifier;
        bool is_focused = false;
        Stage *owner;
        Rectangle bounds;

    public:
        /**
         * Virtual destructor for the ComponentBase class.
         * Ensures proper cleanup of resources in derived classes.
         */
        virtual ~ComponentBase() = default;
        /**
         * Constructs a ComponentBase with the specified identifier and owner stage.
         *
         * @param identifier A unique identifier for the component.
         * @param owner A pointer to the Stage instance that owns this component.
         */
        explicit ComponentBase(const char *identifier, Stage *owner);
        /**
         * Constructs a ComponentBase instance with the specified identifier, owner stage,
         * and bounding rectangle dimensions.
         *
         * @param identifier A constant character pointer representing the unique identifier for the component.
         * @param owner A pointer to the Stage object that owns this component.
         * @param x The x-coordinate of the top-left corner of the component's bounding rectangle.
         * @param y The y-coordinate of the top-left corner of the component's bounding rectangle.
         * @param width The width of the component's bounding rectangle.
         * @param height The height of the component's bounding rectangle.
         */
        explicit ComponentBase(const char *identifier, Stage *owner, int x, int y, int width, int height);
        /**
         * Renders the visual representation of the component.
         *
         * This method is intended to be overridden by derived classes to implement
         * custom drawing logic. By default, it performs no operations.
         */
        virtual void draw() {}
        /**
         * Updates the component's state or behavior based on the current mouse position.
         * This function can be overridden by derived classes to implement custom behavior
         * that reacts to the mouse cursor's location.
         *
         * @param mouse_x The x-coordinate of the mouse cursor.
         * @param mouse_y The y-coordinate of the mouse cursor.
         */
        virtual void update(int mouse_x, int mouse_y) {}

        /**
         * Updates the component behavior over time.
         * This method is called to apply any time-dependent updates
         * to the component's functionality.
         *
         * @param delta_time The time elapsed since the last update call, in seconds.
         */
        virtual void update(float delta_time){}

        /**
         * Retrieves the unique identifier associated with the component.
         *
         * @return A constant character pointer representing the component's identifier.
         */
        virtual const char *get_identifier();
        /**
         * Sets the focused state of the component.
         *
         * @param is_focused True to set the component as focused, false to set it as unfocused.
         */
        void set_focused(bool is_focused);
        /**
         * Retrieves the unique identifier associated with this component.
         *
         * @return A pointer to the character string representing the component's identifier.
         */
        const char *get_identifier() const;

        /**
         * Sets the width of the component to the specified value.
         *
         * @param width The new width of the component, provided as an integer value.
         */
        virtual void set_width(int width);
        /**
         * Sets the height of the component.
         *
         * @param height The new height value, specified as an integer.
         */
        virtual void set_height(int height);
        /**
         * Sets the position of the component by specifying the x and y coordinates.
         *
         * @param x The x-coordinate to set for the component's position.
         * @param y The y-coordinate to set for the component's position.
         */
        virtual void set_position(int x, int y);
        /**
         * Retrieves the height of the component based on its bounding rectangle.
         *
         * @return The height of the component as an integer.
         */
        virtual int get_height() const;
        /**
         * Retrieves the width of the component as an integer value.
         *
         * @return The width of the component, calculated from its bounding dimensions.
         */
        virtual int get_width() const;
        /**
         * Retrieves the x-coordinate of the component's bounding rectangle.
         *
         * @return The x-coordinate, represented as an integer.
         */
        virtual int get_x() const;
        /**
         * Retrieves the y-coordinate of the component's bounding rectangle.
         *
         * @return The y-coordinate as an integer.
         */
        virtual int get_y() const;

        /**
         * Draws a texture stretched or resized to fill a specified rectangle.
         *
         * @param width The width of the rectangle to fill.
         * @param height The height of the rectangle to fill.
         * @param x The x-coordinate of the rectangle's position.
         * @param y The y-coordinate of the rectangle's position.
         * @param texture The texture to be drawn within the rectangle.
         * @param tint The color modulation to apply to the texture during rendering.
         */
        static void draw_texture_to_fill_rect(int width, int height, int x, int y, const Texture2D &texture, Color tint = WHITE);
        /**
         * Draws a texture scaled to a defined scale factor at a specific position
         * on the screen with a specified tint color.
         *
         * @param scale The factor by which the texture should be scaled.
         * @param x The x-coordinate on the screen where the texture will be drawn.
         * @param y The y-coordinate on the screen where the texture will be drawn.
         * @param texture The texture to be drawn.
         * @param tint The color tint to be applied to the texture.
         */
        static void draw_texture_scaled(float scale, float x, float y, const Texture2D &texture, Color tint = WHITE);
        /**
         * Renders a given texture scaled to fit within the specified dimensions, preserving its aspect ratio,
         * and applies a specified color tint to the texture during rendering.
         *
         * @param width The width of the scaled texture. If value is less than or equal to zero,
         *              it will be calculated based on the height to maintain aspect ratio.
         * @param height The height of the scaled texture. If value is less than or equal to zero,
         *               it will be calculated based on the width to maintain aspect ratio.
         * @param x The x-coordinate of the position where the texture should be drawn,
         *          adjusted based on its scaled size.
         * @param y The y-coordinate of the position where the texture should be drawn,
         *          adjusted based on its scaled size.
         * @param texture The texture object to be drawn to the screen.
         * @param tint The color tint to apply to the texture during rendering.
         */
        static void draw_texture_scaled(int width, int height, int x, int y, const Texture2D &texture, Color tint = WHITE);
        /**
         * Scales the given texture dimensions (width and height) proportionally to fit within the texture's original aspect ratio.
         * If one of the dimensions is non-positive, it will be calculated to preserve the aspect ratio based on the other dimension.
         * If both dimensions are positive, the texture is scaled proportionally to fit within the provided dimensions.
         *
         * @param width Reference to the desired width of the texture. Will be updated to the scaled value.
         * @param height Reference to the desired height of the texture. Will be updated to the scaled value.
         * @param texture The texture whose dimensions and aspect ratio will be used for scaling.
         */
        static void scale_texture(int &width, int &height, const Texture2D &texture);
    };
} // namespace artifact
