#ifndef NOTEPADANIMATOR_NOTEPADCONTROLLER_HPP
#define NOTEPADANIMATOR_NOTEPADCONTROLLER_HPP

// -- includes --
#include <windows.h>
#include <functional>

//the main class that controls the notepad.exe process through WinAPI
class NotepadController {
public:
    //start new instance of notepad.exe
    void StartNew();
    //the title bar handle
    HWND WindowHandle;
    //the main text handle
    HWND EditHandle;
    //set title of the process (WindowHandle)
    void SetTitle(const std::string& text) const;
    //set text inside the notepad (EditHandle)
    void SetText(const std::string& text) const;
    //add text to already existing text in the notepad (EditHandle)
    void AddText(const std::string& text) const;
    //move caret to some x y pos
    void MoveCaret(int x, int y) const;
    //move caret to the latest character
    void MoveCaretDown() const;
    //the same as MoveCaret(), but has a length property
    void CreateSelection(int x, int y, int length) const;
    //write a character, instead of setting the whole text
    void WriteCharacter(char character) const;
    //maximize the whole notepad window
    void Maximize();
    //convert the x and y values to a character position
    [[nodiscard]] int ConvertXYToChar(int x, int y) const;
    //split string with a delimiter
    // "hello>world" --> ["hello", "world"]
    [[nodiscard]] static std::vector<std::string> SplitString(std::string original, const std::string& delimiter);
    //get the text inside the notepad (EditHandle)
    [[nodiscard]] std::string GetText() const;
    //wait for text to be entered that matches the needs of the callback
    //each time a character is added, the callback is called and if the output is TRUE, it returns the text entered
    std::string WaitForInput(const std::function<bool(const std::string&)>& callback) const;
    //same as the top function, but if the callback returns FALSE, it calls the errorCallback
    std::string WaitForInput(const std::function<bool(const std::string&)>& callback, const std::function<void()>& errorCallback) const;
private:
    //returned from StartProcess
    STARTUPINFO siNotepadStartupInfo;
    //returned from StartProcess
    PROCESS_INFORMATION piNotepadProcessInfo;
};


#endif //NOTEPADANIMATOR_NOTEPADCONTROLLER_HPP
