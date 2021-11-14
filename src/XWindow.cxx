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

void XWindow::raise()
{
    XEvent event;
    event.type = ClientMessage;
    event.xclient.display = m_system.getDisplay();
    event.xclient.window = m_window;
    event.xclient.message_type = XInternAtom(m_system.getDisplay(), "_NET_ACTIVE_WINDOW", true);
    event.xclient.format = 32;
    event.xclient.data.l[0] = 2L;
    event.xclient.data.l[1] = CurrentTime;
    XSendEvent(m_system.getDisplay(), m_system.getRoot(), false, SubstructureNotifyMask | SubstructureRedirectMask, &event);
    XFlush(m_system.getDisplay());
}
#endif
