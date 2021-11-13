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
};

#endif

#endif