//
// Created by User on 03.02.2021.
//

#ifndef NOTEPADANIMATOR_DIRECTORYHELPER_HPP
#define NOTEPADANIMATOR_DIRECTORYHELPER_HPP

#include <string>
#include <filesystem>
namespace fs = std::filesystem;
class DirectoryHelper {
public:
    static void CheckDirectories();
    static std::vector<fs::path> SortFiles(const std::wstring& path);
};

#endif //NOTEPADANIMATOR_DIRECTORYHELPER_HPP
