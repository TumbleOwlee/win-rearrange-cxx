#ifndef HXX_XSYSTEM
#define HXX_XSYSTEM

#ifdef __unix__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>

class XWindow;

class XSystem 
{
public:
    XSystem();

    Display* getDisplay();

    int getScreen();

    Window getRoot();

    std::vector<XWindow> getWindowStack();

private:
    Display* m_display;
    int m_screen;
    Window m_root;

    void traverseWindowStack(std::vector<XWindow>& outStack, Window entry);
};

#endif

#endif
