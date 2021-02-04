#include <iostream>
#include "NotepadController.hpp"
#include <filesystem>
#include <thread>
#include "DirectoryHelper.hpp"
#include "FfmpegHelper.hpp"
#include "FrameConverter.hpp"
int main() {
    NotepadController nc{};
    nc.StartNew();
    nc.SetText("Welcome to NotepadAnimator!\nPlease, enter the path of your video:\n");
    nc.MoveCaretDown();
    auto videoPath = nc.WaitForInput([](const std::string& string){
        return !string.empty() && std::filesystem::exists(string) && std::filesystem::is_regular_file(string);
    });
    nc.MoveCaretDown();
    nc.AddText("\nOK, you selected a valid file.\nThe program will start in 5 seconds..");
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    nc.SetText("[0%] Making additional checks.. ");
    DirectoryHelper::CheckDirectories();
    nc.AddText("OK\n[20%] Splitting video into images.. ");
    FfmpegHelper::SplitFrames(videoPath);
    nc.AddText("OK\n[40%] Getting audio from the video.. ");
    FfmpegHelper::SplitAudio(videoPath);
    nc.AddText("OK\n");
    FrameConverter::InitializeGdiplus();
    std::cout << FrameConverter::Convert("Frames/Input/100.png");
    std::cin.get();
    return 0;
}
