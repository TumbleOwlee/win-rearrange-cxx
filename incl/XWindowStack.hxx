#ifndef HXX_XSYSTEM
#define HXX_XSYSTEM

#ifdef __unix__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>

class WindowHandle;

class WindowStack 
{
public:
    WindowStack();

    Display* getDisplay();

    int getScreen();

    Window getRoot();

    std::vector<WindowHandle> getWindows();

    void applyOrder(std::vector<WindowHandle*>& windows);

private:
    Display* m_display;
    int m_screen;
    Window m_root;

    void traverseWindowStack(std::vector<WindowHandle>& outStack, Window entry);
};

#endif

#endif
