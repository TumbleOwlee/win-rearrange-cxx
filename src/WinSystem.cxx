#ifdef _WIN32
#include "WinSystem.hxx"
#include "WinWindow.hxx"
#include "utils.hxx"

#include <string>
#include <windows.h>
#include <locale>
#include <codecvt>

BOOL CALLBACK enumerateWindowCallback(HWND hwnd, LPARAM lparam)
{
    // Get passed stack pointer
    std::vector<WinWindow>& pStack = *reinterpret_cast<std::vector<WinWindow>*>(lparam);
    // Initialize buffer
    const DWORD MAX_TITLE_SIZE = 1024;
    char titleBuffer[MAX_TITLE_SIZE];
    // Retrieve title
    GetWindowTextA(hwnd, &titleBuffer[0], MAX_TITLE_SIZE);
    int length = ::GetWindowTextLength(hwnd);
    std::string title(&titleBuffer[0]);
    // Return if Program Manager
    if ((title == "Program Manager") || (length <= 0))
    { 
        return TRUE;
    }
    // Push back new WinWindow
    pStack.emplace_back(hwnd, title);
    return TRUE;
}

WinSystem::WinSystem()
{
}

std::vector<WinWindow> WinSystem::getWindowStack()
{
    std::vector<WinWindow> stack;
    EnumWindows(&enumerateWindowCallback, reinterpret_cast<LPARAM>(&stack));
    return stack;
}

#endif
