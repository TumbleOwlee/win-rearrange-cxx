#ifdef __unix__
#include "XWindowHandle.hxx"
#include "XWindowStack.hxx"
#include "utils.hxx"

WindowHandle::WindowHandle(WindowStack& stack, Window window, std::string name)
    : m_stack(stack)
    , m_window(window)
    , m_name(name)
{
}

std::string WindowHandle::getName() 
{
    return m_name;
}

void WindowHandle::moveAndResize(int x, int y, unsigned int width, unsigned int height) 
{
    XMoveResizeWindow(m_stack.getDisplay(), m_window, x, y, width, height);
}

Window WindowHandle::get()
{
    return m_window;
}
#endif
