#ifndef HXX_UTILS
#define HXX_UTILS

#include <iostream>

#define LOG_DEBUG(X) do { std::cout << "DEBUG: " << X << std::endl; } while(0);

#define LOG_INFO(X)  do { std::cout << " INFO: " << X << std::endl; } while(0);

#define LOG_WARN(X)  do { std::cout << " WARN: " << X << std::endl; } while(0);

#define LOG_ERROR(X) do { std::cout << "ERROR: " << X << std::endl; } while(0);

#endif
