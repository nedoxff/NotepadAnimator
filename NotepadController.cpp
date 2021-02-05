#include <iostream>
#include <thread>
#include <chrono>
#include "NotepadController.hpp"
#include "MainWindowFinder.hpp"
#include "StringHelper.hpp"

void NotepadController::StartNew() {
    std::string notepad = "notepad.exe";
    if(!CreateProcessA(nullptr,
                   const_cast<char*>(notepad.c_str()),
                   nullptr,
                   nullptr,
                   FALSE,
                   0,
                   nullptr,
                   nullptr,
                   &siNotepadStartupInfo,
                   &piNotepadProcessInfo))
    {
        std::cout << "Failed to start notepad.exe!\n" << GetLastError() << std::endl;
    }
    else
    {
        if(WaitForInputIdle(piNotepadProcessInfo.hProcess, 5000) == 0) {
            WindowHandle = FindTopWindow(piNotepadProcessInfo.dwProcessId);
            EditHandle = FindWindowExA(WindowHandle, nullptr, "Edit", nullptr);
        }
    }
}

void NotepadController::SetText(const std::string& text) const {
    SendMessage(EditHandle, WM_SETTEXT, 0, (LPARAM)text.c_str());
}

void NotepadController::SetTitle(const std::string& text) const {
    SendMessage(WindowHandle, WM_SETTEXT, 0, (LPARAM)text.c_str());
}


std::string NotepadController::WaitForInput(const std::function<bool(const std::string &)>& callback) const {
    char* cpCurrent = new char[2048];
    char* cpLoopCurrent = new char[2048];
    SendMessageA(EditHandle, WM_GETTEXT, (WPARAM)2048, (LPARAM)cpCurrent);
    std::string sCurrent = std::string(cpCurrent);
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        SendMessageA(EditHandle, WM_GETTEXT, (WPARAM)2048, (LPARAM)cpLoopCurrent);
        if(strcmp(cpCurrent, cpLoopCurrent) != 0)
        {
            std::string sLoopCurrent = std::string(cpLoopCurrent);
            std::string sReplacedLoopCurrent = ReplaceString(sLoopCurrent, sCurrent, "");
            if(callback(sReplacedLoopCurrent))
                return sReplacedLoopCurrent;
        }
    }
}

std::string NotepadController::WaitForInput(const std::function<bool(const std::string &)> &callback,
                                            const std::function<void()> &errorCallback) const {
    char* cpCurrent = new char[2048];
    char* cpLoopCurrent = new char[2048];
    SendMessageA(EditHandle, WM_GETTEXT, (WPARAM)2048, (LPARAM)cpCurrent);
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        SendMessageA(EditHandle, WM_GETTEXT, (WPARAM)2048, (LPARAM)cpLoopCurrent);
        if(strcmp(cpCurrent, cpLoopCurrent) != 0)
        {
            std::string sLoopCurrent = std::string(cpLoopCurrent);
            if(callback(sLoopCurrent))
                return sLoopCurrent;
            else
                errorCallback();
        }
    }
}

void NotepadController::AddText(const std::string &text) const {
    char* cpCurrentText = new char[65535];
    SendMessage(EditHandle, WM_GETTEXT, (WPARAM)65535, (LPARAM)cpCurrentText);
    std::string sCurrentText = std::string(cpCurrentText);
    sCurrentText += text;
    SendMessage(EditHandle, WM_SETTEXT, 0, (LPARAM)sCurrentText.c_str());
}

std::string NotepadController::GetText() const {
    char* cpCurrentText = new char[65535];
    SendMessage(EditHandle, WM_GETTEXT, (WPARAM)65535, (LPARAM)cpCurrentText);
    std::string sCurrentText = std::string(cpCurrentText);
    return sCurrentText;
}

std::vector<std::string> NotepadController::SplitString(std::string original, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos;
    std::string token;
    while ((pos = original.find(delimiter)) != std::string::npos) {
        token = original.substr(0, pos);
        tokens.push_back(token);
        original.erase(0, pos + delimiter.length());
    }
    return tokens;
}

void NotepadController::MoveCaret(int x, int y) const {
    std::string sText = GetText();
    std::vector<std::string> vSplitString = SplitString(sText, "\n");
    int charPos;
    if(!vSplitString.empty())
        charPos = (y * static_cast<int>(vSplitString[0].length())) + x + y;
    else
        charPos = x;
    SendMessage(EditHandle, EM_SETSEL, charPos, charPos);
}

void NotepadController::MoveCaretDown() const {
    SendMessage(EditHandle, EM_SETSEL, 0, -1);
    SendMessage(EditHandle, EM_SETSEL, -1, -1);
}





