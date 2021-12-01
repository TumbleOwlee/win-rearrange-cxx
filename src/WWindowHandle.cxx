#ifdef _WIN32
#include "WWindowHandle.hxx"
#include "utils.hxx"

WindowHandle::WindowHandle(HWND window, std::string name)
    : m_window(window)
    , m_name(name)
{
}

std::string WindowHandle::getName() 
{
    return m_name;
}

void WindowHandle::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
    MoveWindow(m_window, x, y, width, height, true);
}

HWND WindowHandle::get()
{ 
    return m_window;
}
#endif
