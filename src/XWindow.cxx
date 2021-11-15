#ifdef __unix__
#include "XWindow.hxx"
#include "XSystem.hxx"
#include "utils.hxx"

XWindow::XWindow(XSystem& system, Window window, std::string name)
    : m_system(system)
    , m_window(window)
    , m_name(name)
{
}

std::string XWindow::getName() 
{
    return m_name;
}

void XWindow::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
    XMoveResizeWindow(m_system.getDisplay(), m_window, x, y, width, height);
}

Window XWindow::getHandle()
{
    return m_window;
}
#endif
