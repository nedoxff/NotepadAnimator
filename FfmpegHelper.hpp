//
// Created by User on 31.01.2021.
//

#ifndef CONSOLEANIMATOR_FFMPEGHELPER_HPP
#define CONSOLEANIMATOR_FFMPEGHELPER_HPP
#include <filesystem>

class FfmpegHelper {
public:
    static void SplitFrames(const std::filesystem::path& path);
    static void SplitAudio(const std::filesystem::path& path);
};


#endif //CONSOLEANIMATOR_FFMPEGHELPER_HPP
