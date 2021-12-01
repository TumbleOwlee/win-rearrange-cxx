#ifndef HXX_WINSYSTEM
#define HXX_WINSYSTEM

#ifdef _WIN32

#include <vector>

class WindowData;

class WindowManager 
{
public:
    WindowManager();

    std::vector<WindowData> getWindowStack();

    void applyOrder(std::vector<WindowData*>& windows);
};

#endif

#endif
