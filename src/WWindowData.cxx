#ifdef _WIN32
#include "WWindowData.hxx"
#include "utils.hxx"

WindowData::WindowData(HWND window, std::string name)
    : m_window(window)
    , m_name(name)
{
}

std::string WindowData::getName() 
{
    return m_name;
}

void WindowData::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
    MoveWindow(m_window, x, y, width, height, true);
}

HWND WindowData::getHandle()
{ 
    return m_window;
}
#endif
