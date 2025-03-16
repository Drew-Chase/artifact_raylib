#pragma once
#include <string>
#include <vector>
#include "raylib.h"

namespace artifact
{
    class SpriteSheet
    {
    private:
        std::string root_path;            // Base path pattern for the animation frames
        std::vector<Texture2D> frames;    // Loaded texture frames
        int frame_count;                  // Total number of frames
        float fps;                        // Frames per second for animation
        float frame_time;                 // Time per frame in seconds
        float current_time;               // Current elapsed time
        int current_frame;                // Current displayed frame index
        bool is_playing;                  // Animation playback state

        // Helper method to format frame numbers correctly
        std::string get_formatted_frame_path(const int frame_number) const;

    public:
        // Constructor
        SpriteSheet(const std::string& root_path, const int frame_count, const float fps);

        // Destructor to clean up textures
        ~SpriteSheet();

        // Load all frames from given path pattern
        void load_frames();

        // Unload all textures
        void unload_frames();

        // Update animation state
        void update(const float delta_time);

        // Draw current frame at position
        void draw(const Vector2 position, const float scale = 1.0f, const Color tint = WHITE) const;
        void draw(const float x, const float y, const float scale = 1.0f, const Color tint = WHITE) const;

        // Animation control methods
        void play();
        void pause();
        void reset();
        void set_frame(const int frame_index);

        // Getters
        int get_current_frame() const { return current_frame; }
        bool is_animation_playing() const { return is_playing; }
        Texture2D get_current_texture() const;
        int get_frame_count() const { return frame_count; }
    };
}