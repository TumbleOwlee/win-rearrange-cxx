#ifdef __unix__
#include "XWindowData.hxx"
#include "XWindowManager.hxx"
#include "utils.hxx"

WindowData::WindowData(WindowManager& system, Window window, std::string name)
    : m_system(system)
    , m_window(window)
    , m_name(name)
{
}

std::string WindowData::getName() 
{
    return m_name;
}

void WindowData::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
    XMoveResizeWindow(m_system.getDisplay(), m_window, x, y, width, height);
}

Window WindowData::getHandle()
{
    return m_window;
}
#endif
