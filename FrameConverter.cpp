// -- includes --
#include "FrameConverter.hpp"
#include <gdiplusinit.h>
#include <sstream>

//the ascii list from the .hpp file
std::string FrameConverter::AsciiList = "@#S%>&+;:.,";

std::string FrameConverter::Convert(const std::filesystem::path &file) {
    std::stringstream result;
    Gdiplus::Bitmap bitmap = Gdiplus::Bitmap(file.wstring().c_str());
    //for converting to text bitmap needs to be grayscale
    ConvertToGrayscale(&bitmap);
    Gdiplus::Color pixel;
    //go through each pixel
    for(int y = 0; y < bitmap.GetHeight(); y += 2)
    {
        for(int x = 0; x < bitmap.GetWidth(); x++)
        {
            //get color (the r g b values are the same)
            bitmap.GetPixel(x, y, &pixel);
            //map (0, 255) to (0, length - 1)
			int index = MapNumbers(pixel.GetR(), 0, 255, 0, AsciiList.length() - 1);
            result << AsciiList[index];
        }
        result << "\n";
    }
    return result.str();
}


//GdiplusStartup
void FrameConverter::InitializeGdiplus() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
}

void FrameConverter::ConvertToGrayscale(Gdiplus::Bitmap *copyTo) {
    Gdiplus::Color pixel;
    Gdiplus::Color newPixel;
    //go through each pixel
    for(int y = 0; y < copyTo->GetHeight(); y += 2)
    {
        for(int x = 0; x < copyTo->GetWidth(); x++)
        {
            copyTo->GetPixel(x, y, &pixel);
            //some cursed formula
            int iGrayValue = (int) (0.299 * pixel.GetR() + 0.587 * pixel.GetG() + 0.114 * pixel.GetB());
            newPixel = Gdiplus::Color(iGrayValue, iGrayValue, iGrayValue);
            copyTo->SetPixel(x, y, newPixel);
        }
    }
}
