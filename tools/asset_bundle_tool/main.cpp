#include <algorithm>
#include <filesystem>
#include <ranges>
#include <raylib.h>
#include <spdlog/spdlog.h>


int main()
{
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("%^[artifact_game/asset_bundle_tool/%s:%#(%!)::%l]%$ %v");
    SPDLOG_INFO("Starting artifact asset bundle tool");

    const std::string image_extensions[] = {"jpg", "jpeg", "png"};
    const std::string audio_extensions[] = {"wav", "mp3", "ogg"};
    for (const std::filesystem::recursive_directory_iterator it("./assets/"); const auto &entry: it)
    {
        if (entry.is_regular_file())
        {
            std::string extension = entry.path().extension().string().substr(1);
            std::ranges::transform(extension, extension.begin(), tolower);
            const bool is_image = std::ranges::find(image_extensions, extension) != std::end(image_extensions);
            const bool is_audio = std::ranges::find(audio_extensions, extension) != std::end(audio_extensions);

            if (is_image || is_audio)
            {
                std::string output_filename = entry.path().filename().string().substr(0, entry.path().filename().string().find_last_of('.'));
                std::ranges::replace(output_filename, '-', '_');
                std::ranges::transform(output_filename, output_filename.begin(), tolower);
                std::string path_relative_to_assets = entry.path().string().substr(entry.path().string().find("assets/") + 7);
                path_relative_to_assets = path_relative_to_assets.substr(0, path_relative_to_assets.length() - entry.path().filename().string().length() - 1);
                const auto output_directory = fmt::format("include/resources/{}", path_relative_to_assets);
                const auto output_file = fmt::format("{}/{}.h", output_directory, output_filename);
                std::filesystem::create_directories(output_directory);
                if (is_image)
                {
                    SPDLOG_INFO("Found image file: {}", entry.path().string());
                    const Image image = LoadImage(entry.path().string().c_str());
                    const int data_size = GetPixelDataSize(image.width, image.height, image.format);
                    const auto text_data = static_cast<char *>(RL_CALLOC(data_size * 6 + 2000, sizeof(char)));

                    int byte_count = 0;
                    byte_count += sprintf(text_data + byte_count, "#pragma once\n#include <raylib.h>\n");
                    byte_count += sprintf(text_data + byte_count, "static unsigned char %s_DATA[%llu] = {", output_filename.c_str(), data_size);
                    for (int i = 0; i < data_size - 1; i++)
                        byte_count += sprintf(text_data + byte_count, "0x%x,", static_cast<unsigned char *>(image.data)[i]);
                    byte_count += sprintf(text_data + byte_count, "0x%x};", static_cast<unsigned char *>(image.data)[data_size - 1]);
                    byte_count += sprintf(text_data + byte_count, "static Image %s = {.data = %s_DATA,.width = %i,.height = %i,.mipmaps = 1,.format = %i};",
                                          output_filename.c_str(), output_filename.c_str(), image.width, image.height, image.format);

                    SaveFileText(output_file.c_str(), text_data);
                    RL_FREE(text_data);
                }
                // Check if extension is in audio_extensions
                else if (is_audio)
                {
                    SPDLOG_INFO("Found audio file: {}", entry.path().string());
                    const Wave wave = LoadWave(entry.path().string().c_str());
                    const int data_size = wave.frameCount * wave.channels * wave.sampleSize / 8;
                    const auto text_data = static_cast<char *>(RL_CALLOC(data_size * 12 + 2000, sizeof(char)));
                    int byte_count = 0;
                    byte_count += sprintf(text_data + byte_count, "#pragma once\n#include <raylib.h>\n");

                    if (wave.sampleSize == 32)
                    {
                        byte_count += sprintf(text_data + byte_count, "static float %s_DATA[%llu] = {", output_filename.c_str(), data_size / 4);
                        for (int i = 1; i < data_size / 4; i++)
                            byte_count += sprintf(text_data + byte_count, "%.4ff,", static_cast<float *>(wave.data)[i - 1]);
                        byte_count += sprintf(text_data + byte_count, "%.4ff};", static_cast<float *>(wave.data)[data_size / 4 - 1]);
                    } else
                    {
                        byte_count += sprintf(text_data + byte_count, "static unsigned char %s_DATA[%i] = {", output_filename.c_str(), data_size);
                        for (int i = 1; i < data_size; i++)
                            byte_count += sprintf(text_data + byte_count, "0x%x,", static_cast<unsigned char *>(wave.data)[i - 1]);
                        byte_count += sprintf(text_data + byte_count, "0x%x};", static_cast<unsigned char *>(wave.data)[data_size - 1]);
                    }

                    byte_count += sprintf(text_data + byte_count, "static Wave %s = {.sampleRate = %i,.sampleSize = %i,.channels = %i,.data = %s_DATA};",
                        output_filename.c_str(), wave.frameCount, wave.sampleSize, wave.channels, output_filename.c_str());

                    SaveFileText(output_file.c_str(), text_data);
                    RL_FREE(text_data);
                }
            } else
                SPDLOG_WARN("Unknown file type: {}", entry.path().string());
        }
    }
}
