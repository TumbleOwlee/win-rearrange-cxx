#ifndef HXX_WINWINDOW
#define HXX_WINWINDOW

#ifdef _WIN32
#include <Windows.h>

class WinWindow 
{
  public:
    WinWindow(HWND window, std::string name);

    std::string getName();
     
    void moveAndResize(int x, int y, unsigned int width, unsigned int height);

    void raise();

  private:
    HWND m_window;
    std::string m_name;
};
 
#endif

#endif
