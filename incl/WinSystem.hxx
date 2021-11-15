#ifndef HXX_WINSYSTEM
#define HXX_WINSYSTEM

#ifdef _WIN32

#include <vector>

class WinWindow;

class WinSystem 
{
public:
    WinSystem();

    std::vector<WinWindow> getWindowStack();

    void applyOrder(std::vector<WinWindow*>& windows);
};

#endif

#endif
