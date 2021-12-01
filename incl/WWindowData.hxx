#ifndef HXX_WINWINDOW
#define HXX_WINWINDOW

#ifdef _WIN32

#include <Windows.h>
#include <string>

class WindowData 
{
public:
    WindowData(HWND window, std::string name);

    std::string getName();

    void moveAndResize(int x, int y, unsigned int width, unsigned int height);

    HWND getHandle();

private:
    HWND m_window;
    std::string m_name;
};

#endif

#endif
