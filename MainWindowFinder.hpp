//
// Created by User on 02.02.2021.
//

#ifndef NOTEPADANIMATOR_MAINWINDOWFINDER_HPP
#define NOTEPADANIMATOR_MAINWINDOWFINDER_HPP

#include <windows.h>
#include <vector>
#include <utility>

BOOL CALLBACK TopWindowCallback(HWND hwnd, LPARAM lParam) {
    auto pParams = reinterpret_cast<std::pair<HWND, DWORD>*>(lParam);

    DWORD processId;
    if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second) {
        // Stop enumerating
        SetLastError(-1);
        pParams->first = hwnd;
        return FALSE;
    }

    // Continue enumerating
    return TRUE;
}

HWND FindTopWindow(DWORD pid) {
    std::pair<HWND, DWORD> params = {0, pid};

    // Enumerate the windows using a lambda to process each window
    BOOL bResult = EnumWindows(TopWindowCallback, (LPARAM) &params);

    if (!bResult && GetLastError() == -1 && params.first) {
        return params.first;
    }

    return 0;
}

#endif //NOTEPADANIMATOR_MAINWINDOWFINDER_HPP
