#ifndef NOTEPADANIMATOR_FRAMECONVERTER_HPP
#define NOTEPADANIMATOR_FRAMECONVERTER_HPP

// -- includes --
#include <string>
#include <filesystem>
#include <windows.h>
#include <gdiplus.h>
#include "NotepadController.hpp"
#pragma comment (lib,"Gdiplus.lib")

class FrameConverter {
public:
    //the list of ascii characters that are used
    //to define the brightness of the pixel
    static std::string AsciiList;
    //convert a bitmap to std::string
    static std::string Convert(const std::filesystem::path& file);
    //convert a color bitmap to a grayscale bitmap
    static void ConvertToGrayscale(Gdiplus::Bitmap* copyTo);
    //call GdiplusStartup()
    static void InitializeGdiplus();
    //just like the arduino's map function
	static long MapNumbers(long x, long in_min, long in_max, long out_min, long out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

};


#endif //NOTEPADANIMATOR_FRAMECONVERTER_HPP
