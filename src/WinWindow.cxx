#ifdef _WIN32
#include "WinWindow.hxx"
#include "utils.hxx"

WinWindow::WinWindow(HWND window, std::string name)
    : m_window(window)
    , m_name(name)
{
}

std::string WinWindow::getName() 
{
    return m_name;
}

void WinWindow::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
    MoveWindow(m_window, x, y, width, height, true);
}

HWND WinWindow::getHandle()
{ 
    return m_window;
}
#endif
