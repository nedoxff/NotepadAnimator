// -- includes --
#include "FfmpegHelper.hpp"
#include <sstream>

void FfmpegHelper::SplitAudio(const std::filesystem::path& path) {
    std::stringstream ffmpegAB;
    ffmpegAB << "ffmpeg.exe -i ";
    ffmpegAB << path.string();
    ffmpegAB << " -y -q:a 0 -map a Audio/extracted.mp3";
    ffmpegAB << " > nul";
    system(ffmpegAB.str().c_str());
}

void FfmpegHelper::SplitFrames(const std::filesystem::path& path) {
    std::stringstream ffmpegAB;
    ffmpegAB << "ffmpeg.exe -r 30 -i ";
    ffmpegAB << path.string();
    ffmpegAB << " -vf scale=-1:64 Frames/Input/%d.png";
    ffmpegAB << " > nul";
    system(ffmpegAB.str().c_str());
}
