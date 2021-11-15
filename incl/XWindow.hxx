#ifndef HXX_XWINDOW
#define HXX_XWINDOW

#ifdef __unix__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>
#include <vector>

class XSystem;

class XWindow
{
public:
    XWindow(XSystem& system, Window window, std::string name);

    std::string getName();

    void moveAndResize(int x, int y, unsigned int width, unsigned int height);

    Window getHandle();

private:
    XSystem& m_system;
    Window m_window;
    std::string m_name;
};

#endif

#endif
