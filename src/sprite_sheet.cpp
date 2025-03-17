#include "sprite_sheet.h"
#include <format>

namespace artifact
{
    SpriteSheet::SpriteSheet(const std::string &root_path, const int frame_count, const float fps) : root_path(root_path), frame_count(frame_count), fps(fps), frame_time(1.0f / fps), current_time(0.0f), current_frame(0), is_playing(true)
    {
        frames.resize(frame_count);
        load_frames();
    }

    SpriteSheet::~SpriteSheet() { unload_frames(); }

    std::string SpriteSheet::get_formatted_frame_path(const int frame_number) const
    {
        // Format frame number with leading zeros if needed
        std::string formatted_number;
        if (frame_number < 10)
        {
            formatted_number = "0" + std::to_string(frame_number);
        } else
        {
            formatted_number = std::to_string(frame_number);
        }

        // Find the last '%d' in the path and replace it
        std::string path = root_path;
        const size_t pos = path.find_last_of('%');
        if (pos != std::string::npos)
        {
            // Remove the '%d' format specifier
            path.erase(pos, 2);
            // Insert the formatted number
            path.insert(pos, formatted_number);
        }

        return path;
    }

    void SpriteSheet::load_frames()
    {
        for (int i = 0; i < frame_count; i++)
        {
            const std::string path = get_formatted_frame_path(i + 1);
            frames[i] = LoadTexture(path.c_str());
        }
    }

    void SpriteSheet::unload_frames()
    {
        for (const auto &texture: frames)
        {
            UnloadTexture(texture);
        }
        frames.clear();
    }

    void SpriteSheet::update(const float delta_time)
    {
        if (!is_playing || frames.empty())
        {
            return;
        }

        current_time += delta_time;

        if (current_time >= frame_time)
        {
            current_frame = (current_frame + 1) % frame_count;
            current_time = 0.0f;
        }
    }

    void SpriteSheet::draw(const Vector2 position, const float scale, const Color tint) const
    {
        if (frames.empty() || current_frame >= frames.size())
        {
            return;
        }

        const Texture2D texture = frames[current_frame];
        const float width = static_cast<float>(texture.width);
        const float height = static_cast<float>(texture.height);
        const Rectangle source = {0, 0, flipped ? -width : width, height};
        const Rectangle dest = {position.x - width / 2, position.y - height, width * scale, height * scale};
        constexpr Vector2 origin = {0, 0};

        DrawTexturePro(texture, source, dest, origin, 0.0f, tint);
    }

    void SpriteSheet::draw(const float x, const float y, const float scale, const Color tint) const { draw(Vector2{x, y}, scale, tint); }

    void SpriteSheet::play() { is_playing = true; }

    void SpriteSheet::pause() { is_playing = false; }

    void SpriteSheet::reset()
    {
        current_frame = 0;
        current_time = 0.0f;
    }

    void SpriteSheet::set_frame(const int frame_index)
    {
        if (frame_index >= 0 && frame_index < frame_count)
        {
            current_frame = frame_index;
            current_time = 0.0f;
        }
    }

    Texture2D SpriteSheet::get_current_texture() const
    {
        if (frames.empty() || current_frame >= frames.size())
        {
            return {0}; // Return empty texture
        }
        return frames[current_frame];
    }
    void SpriteSheet::set_flipped(const bool flipped) { this->flipped = flipped; }
    bool SpriteSheet::is_flipped() const { return flipped; }
    void SpriteSheet::set_framerate(const float fps)
    {
        this->fps = fps;
        frame_time = 1.0f / fps;
    }
} // namespace artifact
