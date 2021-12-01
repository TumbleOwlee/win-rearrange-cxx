#ifdef _WIN32
#include "WWindowManager.hxx"
#include "WWindowData.hxx"
#include "utils.hxx"

#include <string>
#include <windows.h>
#include <locale>
#include <codecvt>

BOOL CALLBACK enumerateWindowCallback(HWND hwnd, LPARAM lparam)
{
    // Get passed stack pointer
    std::vector<WindowData>& pStack = *reinterpret_cast<std::vector<WindowData>*>(lparam);
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
    // Push back new WindowData
    pStack.emplace_back(hwnd, title);
    return TRUE;
}

WindowManager::WindowManager()
{
}

std::vector<WindowData> WindowManager::getWindowStack()
{
    std::vector<WindowData> stack;
    EnumWindows(&enumerateWindowCallback, reinterpret_cast<LPARAM>(&stack));
    return stack;
}

void WindowManager::applyOrder(std::vector<WindowData*>& windows)
{
    HDWP hdwp = BeginDeferWindowPos(windows.size());
    WindowData* parent = nullptr;
    for (auto iter = windows.begin(); iter != windows.end(); ++iter)
    {
        if (iter == windows.begin())
        {
            hdwp = DeferWindowPos(hdwp, (*iter)->getHandle(), HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE);
        }
        else 
        {
            hdwp = DeferWindowPos(hdwp, (*iter)->getHandle(), parent->getHandle(), 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOSIZE);
        }
        parent = (*iter);
    }
    EndDeferWindowPos(hdwp);
}
#endif
