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

void NotepadController::MoveCaret(int x, int y) const {
    SendMessage(EditHandle, EM_SETSEL, x, y);
}

void NotepadController::MoveCaretDown() const {
    MoveCaret(0, -1);
    MoveCaret(-1, -1);
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






