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
	static long MapNumbers(long x, long in_min, long in_max, long out_min, long out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
};


#endif //NOTEPADANIMATOR_FRAMECONVERTER_HPP
