#ifndef HXX_WINSYSTEM
#define HXX_WINSYSTEM

#ifdef _WIN32

#include <vector>

class WindowHandle;

class WindowStack 
{
public:
    WindowStack();

    std::vector<WindowHandle> getWindows();

    void applyOrder(std::vector<WindowHandle*>& windows);
};

#endif

#endif
