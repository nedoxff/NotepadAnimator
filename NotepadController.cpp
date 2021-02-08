// -- includes --
#include <iostream>
#include <thread>
#include <chrono>
#include "NotepadController.hpp"
#include "MainWindowFinder.hpp"
#include "StringHelper.hpp"

void NotepadController::StartNew() {
    //using some cursed WinAPI code
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
        //in this code i separate the WindowHandle (the title bar)
        //and the EditHandle (the main text)
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
    //get the already entered text
    SendMessageA(EditHandle, WM_GETTEXT, (WPARAM)2048, (LPARAM)cpCurrent);
    std::string sCurrent = std::string(cpCurrent);
    while(true)
    {
        //need some delay or else the program will halt
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //get the text again
        SendMessageA(EditHandle, WM_GETTEXT, (WPARAM)2048, (LPARAM)cpLoopCurrent);
        //check if strings are not equal (that's for c-styled strings, sadly)
        if(strcmp(cpCurrent, cpLoopCurrent) != 0)
        {
            //the differences between these strings IS the user input, which i need
            std::string sLoopCurrent = std::string(cpLoopCurrent);
            std::string sReplacedLoopCurrent = ReplaceString(sLoopCurrent, sCurrent, "");
            if(callback(sReplacedLoopCurrent)) {
                //free memory
                delete[] cpCurrent;
                delete[] cpLoopCurrent;
                return sReplacedLoopCurrent;
            }
        }
    }
}


//IT'S THE SAME FOR THE UPPER METHOD, JUST WITH AN ERROR CALLBACK!!!
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
            if(callback(sLoopCurrent)) {
                delete[] cpCurrent;
                delete[] cpLoopCurrent;
                return sLoopCurrent;
            }
            else
                errorCallback();
        }
    }
}

void NotepadController::AddText(const std::string &text) const {
    char* cpCurrentText = new char[65535];
    //get current text
    SendMessage(EditHandle, WM_GETTEXT, (WPARAM)65535, (LPARAM)cpCurrentText);
    //for convenience convert to string
    std::string sCurrentText = std::string(cpCurrentText);
    //add text and push it back
    sCurrentText += text;
    SendMessage(EditHandle, WM_SETTEXT, 0, (LPARAM)sCurrentText.c_str());
}

//just calling the WinAPI function and convert the output to string
std::string NotepadController::GetText() const {
    char* cpCurrentText = new char[65535];
    SendMessage(EditHandle, WM_GETTEXT, (WPARAM)65535, (LPARAM)cpCurrentText);
    std::string sCurrentText = std::string(cpCurrentText);
    return sCurrentText;
}

//Split string by delimiter
//WARNING: COMPLETELY COPIED FROM STACKOVERFLOW!!
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
    //winapi doesn't accept x and y poses, so convert them to character positions
    int iCharPos = ConvertXYToChar(x, y);
    SendMessage(EditHandle, EM_SETSEL, iCharPos, iCharPos);
}

void NotepadController::MoveCaretDown() const {
    //some winapi trickery
    SendMessage(EditHandle, EM_SETSEL, 0, -1);
    SendMessage(EditHandle, EM_SETSEL, -1, -1);
}

int NotepadController::ConvertXYToChar(int x, int y) const {
    //get the current text
    std::string sText = GetText();
    //split it by \n's
    std::vector<std::string> vSplitString = SplitString(sText, "\n");
    int charPos;
    if(!vSplitString.empty())
        //charPos = (y * line length) + x + y
        charPos = (y * static_cast<int>(vSplitString[0].length())) + x + y;
    else
        //if there's only one line, the position is just X
        charPos = x;
    return charPos;
}

void NotepadController::WriteCharacter(char character) const {
    SendMessage(EditHandle, WM_CHAR, (int)character, 0);
}

//same as MoveCaret, but now for WPARAM it adds the length
void NotepadController::CreateSelection(int x, int y, int length) const {
    int iCharPos = ConvertXYToChar(x, y);
    SendMessage(EditHandle, EM_SETSEL, iCharPos, iCharPos + length);
}

void NotepadController::Maximize() {
    ShowWindow(WindowHandle, SW_MAXIMIZE);
}





