#ifndef HXX_WINWINDOW
#define HXX_WINWINDOW

#ifdef _WIN32

#include <Windows.h>
#include <string>

class WindowHandle
{
public:
    WindowHandle(HWND window, std::string name);

    std::string getName();

    void moveAndResize(int x, int y, unsigned int width, unsigned int height);

    HWND get();

private:
    HWND m_window;
    std::string m_name;
};

#endif

#endif
