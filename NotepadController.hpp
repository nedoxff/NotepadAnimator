//
// Created by User on 02.02.2021.
//

#ifndef NOTEPADANIMATOR_NOTEPADCONTROLLER_HPP
#define NOTEPADANIMATOR_NOTEPADCONTROLLER_HPP

#include <windows.h>
#include <functional>

class NotepadController {
public:
    void StartNew();
    HWND WindowHandle;
    HWND EditHandle;
    void SetTitle(const std::string& text) const;
    void SetText(const std::string& text) const;
    void AddText(const std::string& text) const;
    void MoveCaret(int x, int y) const;
    void MoveCaretDown() const;
    static std::vector<std::string> SplitString(std::string original, const std::string& delimiter);
    std::string GetText() const;
    std::string WaitForInput(const std::function<bool(const std::string&)>& callback) const;
    std::string WaitForInput(const std::function<bool(const std::string&)>& callback, const std::function<void()>& errorCallback) const;
private:
    STARTUPINFO siNotepadStartupInfo;
    PROCESS_INFORMATION piNotepadProcessInfo;
};


#endif //NOTEPADANIMATOR_NOTEPADCONTROLLER_HPP
