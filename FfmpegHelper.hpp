#ifndef CONSOLEANIMATOR_FFMPEGHELPER_HPP
#define CONSOLEANIMATOR_FFMPEGHELPER_HPP

// -- includes --
#include <filesystem>

class FfmpegHelper {
public:
    //get frames (.png) from the video
    static void SplitFrames(const std::filesystem::path& path);
    //get audio (.mp3) from the video
    static void SplitAudio(const std::filesystem::path& path);
};


#endif //CONSOLEANIMATOR_FFMPEGHELPER_HPP
