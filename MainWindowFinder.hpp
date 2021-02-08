#ifndef NOTEPADANIMATOR_MAINWINDOWFINDER_HPP
#define NOTEPADANIMATOR_MAINWINDOWFINDER_HPP

// -- includes --
#include <windows.h>
#include <vector>
#include <utility>

//WARNING: COMPLETELY COPIED FROM STACKOVERFLOW!!!

BOOL CALLBACK TopWindowCallback(HWND hwnd, LPARAM lParam) {
    auto pParams = reinterpret_cast<std::pair<HWND, DWORD>*>(lParam);
    DWORD processId;
    if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second) {
        SetLastError(-1);
        pParams->first = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND FindTopWindow(DWORD pid) {
    std::pair<HWND, DWORD> params = {0, pid};
    BOOL bResult = EnumWindows(TopWindowCallback, (LPARAM) &params);
    if (!bResult && GetLastError() == -1 && params.first) {
        return params.first;
    }
    return nullptr;
}

#endif //NOTEPADANIMATOR_MAINWINDOWFINDER_HPP
