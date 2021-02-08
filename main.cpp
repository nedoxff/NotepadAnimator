// -- includes --
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#include <iostream>
#include "NotepadController.hpp"
#include <filesystem>
#include <thread>
#include "DirectoryHelper.hpp"
#include "FfmpegHelper.hpp"
#include "FrameConverter.hpp"

// -- main code --
int main() {
    NotepadController nc{};
    nc.StartNew();
    nc.Maximize();
    nc.SetText("Welcome to NotepadAnimator!\nPlease, enter the path of your video:\n");
    nc.MoveCaretDown();
    // -- wait for an existing file --
    auto videoPath = nc.WaitForInput([](const std::string& string){
        return !string.empty() && std::filesystem::exists(string) && std::filesystem::is_regular_file(string);
    });
    nc.MoveCaretDown();
    // -- starting to work --
    nc.AddText("\nOK, you selected a valid file.\nThe program will start in 5 seconds..");
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // -- check if Frames and Audio directories exist --
    nc.SetText("Making additional checks.. ");
    DirectoryHelper::CheckDirectories();
    // -- split video into 64p frames --
    nc.AddText("OK\nSplitting video into images.. ");
    FfmpegHelper::SplitFrames(videoPath);
    // -- get audio from the video --
    nc.AddText("OK\nGetting audio from the video.. ");
    FfmpegHelper::SplitAudio(videoPath);
    // -- render frames --
    nc.AddText("OK\nConverting frames to text.. ");
    // -- GdiplusStartup() --
    FrameConverter::InitializeGdiplus();
    // -- sort files by their numbers in the filepath --
    // -- example --
    /*
     * 1.jpg
     * 100.jpg
     * 1000.jpg
     * -- becomes --
     * 1.jpg
     * 2.jpg
     * 3.jpg
     * ...
     */
    auto files = DirectoryHelper::SortFiles(L"Frames/Input");
    std::vector<std::string> frames;
    // -- main part of rendering --
    int count = 0;
    for(auto& f : files) {
        frames.push_back(FrameConverter::Convert(f));
        count++;
    }
    nc.AddText("OK");
    // -- wait a second before allowing to play --
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    nc.SetText("Press P to start playing!\n");
    nc.MoveCaretDown();
    nc.WaitForInput([](const std::string& string){
        return string == "p" || string == "P";
    });
    // -- counts the amount of frames drawn before skipping a frame --
    // min: 0 max: 2
    // in the main loop:
    /*
     * 0
     * 1
     * 2
     * skip
     * 0
     * ...
     */
    int skipCount = 0;
    // -- the amount of frames skipped --
    // used for debugging
    // min: 0 max: ?
    int droppedFrames = 0;
    // -- 1second / 30fps --
    int frameDelay = 1000 / 30;
    // -- WinAPI function to start playing sound --
    mciSendString("play Audio/extracted.mp3", nullptr, 0, nullptr);
    for(int i = 0; i < files.size(); i++)
    {
        skipCount++;
        //if its time to skip
        if(skipCount == 3)
        {
            skipCount = 0;
            droppedFrames++;
            //we dont draw anything, so it takes 0ms and we can wait the full amount
            //of delay
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay));
            continue;
        }
        auto start = std::chrono::system_clock::now();
        nc.SetText(frames[i]);
        //additional debugging
        std::cout << "FPS Delay: " << frameDelay << " Dropped frames (limit to 10fps): " << droppedFrames << " Skip Count: " << skipCount + 1 << std::endl;
        //the time of setting text ranges from 3-7ms, so i need to calculate how much to wait
        // 33ms - elapsed
        std::this_thread::sleep_until(start + std::chrono::milliseconds(frameDelay));
    }

    return 0;
}