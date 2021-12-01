#ifndef HXX_XSYSTEM
#define HXX_XSYSTEM

#ifdef __unix__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>

class WindowData;

class WindowManager 
{
public:
    WindowManager();

    Display* getDisplay();

    int getScreen();

    Window getRoot();

    std::vector<WindowData> getWindowStack();

    void applyOrder(std::vector<WindowData*>& windows);

private:
    Display* m_display;
    int m_screen;
    Window m_root;

    void traverseWindowStack(std::vector<WindowData>& outStack, Window entry);
};

#endif

#endif
