//
// Created by User on 03.02.2021.
//

#ifndef NOTEPADANIMATOR_FRAMECONVERTER_HPP
#define NOTEPADANIMATOR_FRAMECONVERTER_HPP
#include <string>
#include <filesystem>
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

class FrameConverter {
public:
    static std::string AsciiList;
    static std::string Convert(const std::filesystem::path& file);
    static void ConvertToGrayscale(Gdiplus::Bitmap* copyTo);
    static void InitializeGdiplus();
};


#endif //NOTEPADANIMATOR_FRAMECONVERTER_HPP
