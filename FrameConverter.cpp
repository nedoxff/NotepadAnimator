#include "FrameConverter.hpp"
#include <gdiplusinit.h>
#include <sstream>

std::string FrameConverter::AsciiList = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

std::string FrameConverter::Convert(const std::filesystem::path &file) {
    std::stringstream result;
    Gdiplus::Bitmap bitmap = Gdiplus::Bitmap(file.wstring().c_str());
    ConvertToGrayscale(&bitmap);
    Gdiplus::Color pixel;
    for(int y = 0; y < bitmap.GetHeight(); y += 2)
    {
        for(int x = 0; x < bitmap.GetWidth(); x++)
        {
            bitmap.GetPixel(x, y, &pixel);
            int index = pixel.GetR() / static_cast<int>(AsciiList.length());
            result << AsciiList[index];
        }
        result << "\n";
    }
    return result.str();
}


void FrameConverter::InitializeGdiplus() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
}

void FrameConverter::ConvertToGrayscale(Gdiplus::Bitmap *copyTo) {
    Gdiplus::Color pixel;
    Gdiplus::Color newPixel;
    for(int y = 0; y < copyTo->GetHeight(); y += 2)
    {
        for(int x = 0; x < copyTo->GetWidth(); x++)
        {
            copyTo->GetPixel(x, y, &pixel);
            int iGrayValue = (int) (0.299 * pixel.GetR() + 0.587 * pixel.GetG() + 0.114 * pixel.GetB());
            newPixel = Gdiplus::Color(iGrayValue, iGrayValue, iGrayValue);
            copyTo->SetPixel(x, y, newPixel);
        }
    }
}
