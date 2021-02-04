#include "DirectoryHelper.hpp"
#include <filesystem>
#include "StringHelper.hpp"
namespace fs = std::filesystem;

std::vector<fs::path> DirectoryHelper::SortFiles(const std::wstring& path) {
    std::vector<fs::path> filenames;
    for (const auto& entry : fs::directory_iterator{path}) {
        if (entry.is_regular_file()) {
            filenames.push_back(entry.path());
        }
    }

    std::sort(filenames.begin(), filenames.end(),
              [](const fs::path& lhs, const fs::path& rhs) {
                  auto replaceLeft  = ReplaceString(ReplaceString(lhs.string(), ".png", ""), "Frames/Input\\", "");
                  auto replaceRight = ReplaceString(ReplaceString(rhs.string(), ".png", ""), "Frames/Input\\", "");
                  return std::stoi(replaceLeft) < std::stoi(replaceRight);
              });

    return filenames;
}

void DirectoryHelper::CheckDirectories() {
    if(!fs::exists("Frames"))
        fs::create_directory("Frames");
    if(!fs::exists("Frames/Input"))
        fs::create_directory("Frames/Input");
    if(!fs::exists("Frames/Output"))
        fs::create_directory("Frames/Output");
    if(!fs::exists("Audio"))
        fs::create_directory("Audio");
}
