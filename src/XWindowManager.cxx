#ifdef __unix__
#include "XWindowManager.hxx"
#include "XWindowData.hxx"
#include "utils.hxx"

#include <string>

WindowManager::WindowManager() 
    : m_display(XOpenDisplay(nullptr))
    , m_screen(XDefaultScreen(m_display))
    , m_root(XDefaultRootWindow(m_display))
{
}

Display* WindowManager::getDisplay()
{ 
    return m_display;
}

int WindowManager::getScreen()
{
    return m_screen;
}

Window WindowManager::getRoot()
{
    return m_root;
}

std::vector<WindowData> WindowManager::getWindowStack()
{  
    std::vector<WindowData> stack;
    traverseWindowStack(stack, m_root);
    return stack;
}

void WindowManager::traverseWindowStack(std::vector<WindowData>& outStack, Window entry)
{ 
    Window root, parent;
    Window* children;
    unsigned int numChildren;

    if (0 != XQueryTree(m_display, entry, &root, &parent, &children, &numChildren))
    {
        for (unsigned int idx = 0U; idx < numChildren; ++idx)
        {
            XWindowAttributes attr;
            XTextProperty prop;
            if ((0 != XGetWindowAttributes(m_display, children[idx], &attr))
                    && (0 != XGetWMName(m_display, children[idx], &prop))
                    && (8 == prop.format)
                    && (attr.width > 1) && (attr.height > 1) && (attr.c_class))
            {
                auto name = std::string(reinterpret_cast<const char*>(prop.value), prop.nitems);
                if (!name.empty())
                {
                    outStack.emplace_back(*this, children[idx], name);
                }
            }
            traverseWindowStack(outStack, children[idx]);
        }
    }
}

void WindowManager::applyOrder(std::vector<WindowData*>& windows)
{
    if (!windows.empty())
    {
        for (auto iter = (windows.end() - 1); iter != windows.begin(); --iter)
        {
            auto handle = (*iter)->getHandle();
            XEvent event;
            event.type = ClientMessage;
            event.xclient.display = m_display;
            event.xclient.window = handle;
            event.xclient.message_type = XInternAtom(m_display, "_NET_ACTIVE_WINDOW", true);
            event.xclient.format = 32;
            event.xclient.data.l[0] = 2L;
            event.xclient.data.l[1] = CurrentTime;
            XSendEvent(m_display, m_root, false, SubstructureNotifyMask | SubstructureRedirectMask, &event);
            XFlush(m_display);
        }
    }
}
#endif
