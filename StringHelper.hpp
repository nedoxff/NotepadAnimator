#ifndef NOTEPADANIMATOR_STRINGHELPER_HPP
#define NOTEPADANIMATOR_STRINGHELPER_HPP

// -- includes --
#include <string>

//replace part of a string with a new string.
//AGAIN COPIED FROM STACKOVERFLOW!!
static std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

#endif //NOTEPADANIMATOR_STRINGHELPER_HPP
