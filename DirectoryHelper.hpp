#ifndef NOTEPADANIMATOR_DIRECTORYHELPER_HPP
#define NOTEPADANIMATOR_DIRECTORYHELPER_HPP

// -- includes --
#include <string>
#include <filesystem>
// -- namespaces --
namespace fs = std::filesystem;


class DirectoryHelper {
public:
    //Check for Audio, Frames, Frames/Input, Frames/Output directories
    static void CheckDirectories();
    //Sort files by their number in the filename
    static std::vector<fs::path> SortFiles(const std::wstring& path);
};

#endif //NOTEPADANIMATOR_DIRECTORYHELPER_HPP
