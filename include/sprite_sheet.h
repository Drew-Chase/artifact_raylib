#pragma once
#include <string>
#include <vector>
#include "raylib.h"

namespace artifact
{
    /**
     * Represents a sprite sheet used for frame-based sprite animations.
     *
     * The SpriteSheet class handles loading, updating, and rendering
     * of individual frames that make up an animated sequence. It supports
     * features like playback control, frame management, and dynamic
     * drawing of frames with scaling and tinting options.
     */
    class SpriteSheet
    {
        /**
         * The base file path pattern for the animation frames.
         *
         * This string stores the root path used to identify and load individual
         * frame files for a sprite sheet animation.
         */
        std::string root_path;
        /**
         * A collection of Texture2D objects representing the individual frames
         * of an animation sequence within a sprite sheet. Each frame corresponds
         * to a static image used for rendering a specific state or position
         * within the animation cycle.
         */
        std::vector<Texture2D> frames;
        /**
         * Represents the total number of frames in the animation sequence.
         *
         * Used to define the length of a sprite sheet animation by specifying
         * how many individual frames make up the animation.
         */
        int frame_count;
        /**
         * Specifies the playback speed of an animation in frames per second.
         *
         * This variable determines how many animation frames are displayed per second,
         * controlling the speed of the animated sequence. A higher value results in faster
         * animation, while a lower value slows it down.
         */
        float fps;
        /**
         * Stores the duration of time allocated for each animation frame.
         *
         * This variable represents the time interval, in seconds, for which each
         * frame of the animation should be displayed during playback.
         */
        float frame_time;
        /**
         * Represents the current time in seconds.
         *
         * This variable is typically used to track elapsed time or synchronize
         * animations, computations, or other time-dependent operations within the
         * context of the application.
         */
        float current_time;
        /**
         * Represents the index of the current frame in the sprite sheet animation.
         *
         * This variable tracks which animation frame is currently being displayed.
         * It is used to manage frame progression and ensure proper frame rendering
         * during playback.
         */
        int current_frame;
        /**
         * Boolean flag indicating whether the animation is currently playing.
         *
         * This variable represents the playback state of the sprite sheet's animation.
         * If set to true, the animation is actively playing. If set to false, the
         * animation is paused or stopped.
         */
        bool is_playing;

        /**
         * Indicates whether an object or sprite is flipped horizontally.
         *
         * The flipped variable is typically used in rendering or animation contexts
         * to determine if the graphical representation of an entity should be mirrored
         * along the horizontal axis. It serves as a flag for controlling visual orientation.
         */
        bool flipped = false;

        /**
         * Generates a fully formatted file path for a specific animation frame.
         *
         * This method replaces the placeholder format specifier in the root_path
         * with the given frame number, properly formatted with leading zeros as needed.
         * It ensures the file path is correctly constructed for loading a specific frame
         * of the animation.
         *
         * @param frame_number The frame number to format, which will replace the frame placeholder.
         * @return A formatted string representing the file path of the specified frame.
         */
        std::string get_formatted_frame_path(const int frame_number) const;

    public:
        /**
         * Constructor for the SpriteSheet class.
         *
         * Initializes a sprite sheet for handling frame-based animation. The root_path
         * specifies the base path pattern for animation frame file names, frame_count
         * determines the total number of frames in the animation, and fps specifies
         * the desired frame rate for playback. Loads all frames and prepares the animation
         * for playback.
         *
         * @param root_path The base file path pattern for the animation frames.
         * @param frame_count The total number of frames in the animation.
         * @param fps The frames-per-second playback speed for the animation.
         */
        SpriteSheet(const std::string &root_path, const int frame_count, const float fps);


        /**
         * Default constructor for the SpriteSheet class.
         *
         * Initializes a SpriteSheet object with default parameters. This constructor
         * does not perform any specific setup or allocate resources, serving as a
         * straightforward way to create an instance of the class.
         */
        SpriteSheet() = default;

        /**
         * Destructor for the SpriteSheet class.
         *
         * Responsible for releasing any resources allocated during the SpriteSheet's
         * lifetime, such as the loaded texture frames. This ensures proper cleanup
         * by invoking the `unload_frames` method to free memory associated with
         * all loaded textures.
         */
        ~SpriteSheet();

        /**
         * @brief Loads all animation frames from the file path pattern.
         *
         * This function iterates through the frame count, formats each frame path
         * based on the provided root path and frame number, then loads the texture
         * for each frame into the vector of frames.
         *
         * @note Assumes that frame numbering starts at 1 and corresponds to the
         * integer values used in the formatted file paths.
         *
         * @see SpriteSheet::get_formatted_frame_path()
         * @see SpriteSheet::unload_frames()
         */
        void load_frames();

        /**
         * Unloads all texture frames stored in the internal frame buffer.
         *
         * This method ensures proper resource cleanup by releasing memory
         * occupied by each texture in the frames vector. After calling this
         * function, the frames vector will be cleared and empty.
         *
         * It is automatically called in the destructor of the SpriteSheet class,
         * but can be used explicitly if needed to manage resources proactively.
         */
        void unload_frames();

        /**
         * Updates the state of the sprite sheet animation. It calculates
         * the progression of the animation based on the elapsed time since
         * the last update.
         *
         * If the sprite sheet animation is currently playing and contains
         * frames, the method advances the animation by adjusting the
         * `current_frame` based on the `delta_time` and `fps`. The method
         * also resets `current_time` once it surpasses the time required
         * for the current frame.
         *
         * @param delta_time The elapsed time in seconds since the last update.
         */
        void update(const float delta_time);

        /**
         * Draws the current frame of the sprite sheet at a specified position with a given scale and tint.
         *
         * This method renders the active frame of the sprite sheet as defined by the `current_frame` index.
         *
         * Position:
         *   - The `position` parameter specifies the world position where the top-left corner of the frame will be drawn.
         *
         * Scaling:
         *   - The `scale` parameter determines how much the frame should be enlarged or reduced.
         *     A value of 1.0 results in drawing the frame at its original pixel size.
         *
         * Tint:
         *   - The `tint` parameter applies a color overlay with transparency to the frame being drawn.
         *
         * Preconditions:
         *   - The sprite sheet's frames must have been loaded successfully via `load_frames()`.
         *   - The `current_frame` must be within `frames`' size to avoid rendering issues.
         *
         * Postconditions:
         *   - The `current_frame` of the sprite sheet is drawn to the screen.
         *
         * Parameters:
         *   position - The 2D position where the sprite frame will be displayed.
         *   scale    - Scaling factor to resize the frame.
         *   tint     - Color tint overlay to apply to the frame.
         */
        void draw(const Vector2 position, const float scale = 1.0f, const Color tint = WHITE) const;
        /**
         * Draws the current frame of the sprite sheet at the specified position.
         *
         * This overloaded method uses individual `x` and `y` float parameters for positioning
         * instead of a single Vector2 structure. The frame is drawn with the provided scaling
         * factor and color tint applied.
         *
         * @param x The x-coordinate on the screen where the sprite frame should be drawn.
         * @param y The y-coordinate on the screen where the sprite frame should be drawn.
         * @param scale The scaling factor to resize the sprite frame.
         * @param tint The color tint to apply to the sprite frame during rendering.
         */
        void draw(const float x, const float y, const float scale = 1.0f, const Color tint = WHITE) const;

        /**
         * @brief Starts or resumes the animation playback.
         *
         * Sets the internal state of the SpriteSheet to indicate that the animation
         * should play. This resets the pause state and allows frame updates to
         * progress during calls to the update method.
         *
         * Does not affect the current frame or time position in the animation.
         */
        void play();
        /**
         * @brief Pauses the animation playback.
         *
         * The animation playback state will be set to paused,
         * preventing updates to the current frame until resumed.
         */
        void pause();
        /**
         * Resets the animation state of the SpriteSheet.
         *
         * This method sets the current frame index to the first frame and resets the
         * elapsed time of the animation to 0.0. It effectively restarts the animation
         * from the beginning.
         */
        void reset();
        /**
         * Sets the current frame of the sprite sheet manually to the specified index.
         *
         * If the provided frame index is within the valid range (0 to frame_count - 1),
         * the `current_frame` will be set to the specified value, and `current_time`
         * will be reset to 0.0f. This allows manual control of the animation's current frame.
         *
         * @param frame_index The index of the frame to set as the current frame.
         *                    Valid values are between 0 and frame_count - 1 (inclusive).
         */
        void set_frame(const int frame_index);

        /**
         * @brief Retrieves the index of the currently displayed animation frame.
         *
         * @return The index of the current frame in the animation sequence.
         */
        int get_current_frame() const { return current_frame; }
        /**
         * @brief Checks if the animation is currently playing.
         *
         * @return True if the animation is in a playing state, false otherwise.
         */
        bool is_animation_playing() const { return is_playing; }
        /**
         * @brief Retrieves the currently displayed texture of the sprite sheet.
         *
         * This function returns the `Texture2D` corresponding to the current
         * animation frame being displayed. If there are no frames loaded or the
         * `current_frame` index is out of range, it returns an empty texture.
         *
         * @return Texture2D The texture for the current animation frame, or an
         *         empty texture if no valid frame is available.
         */
        Texture2D get_current_texture() const;
        /**
         * @brief Retrieves the total number of frames in the sprite sheet animation.
         *
         * @return The total frame count as an integer.
         */
        int get_frame_count() const { return frame_count; }
        /**
         * Sets the flipped state of the sprite sheet.
         *
         * Changes the orientation of the sprite sheet by determining
         * whether its frames should be drawn flipped horizontally.
         *
         * @param flipped A boolean value indicating the desired flipped state.
         *                If true, the sprite sheet will be rendered flipped
         *                horizontally; otherwise, it will be rendered normally.
         */
        void set_flipped(bool flipped);
        /**
         * Checks if the sprite sheet is currently flipped horizontally.
         *
         * This method determines whether the sprite sheet's frames are rendered
         * in a horizontally flipped orientation, which can be used for effects
         * like mirroring or directional sprites in animations.
         *
         * @return True if the sprite sheet is flipped horizontally, false otherwise.
         */
        bool is_flipped() const;

        void set_framerate(float fps);
    };
} // namespace artifact
