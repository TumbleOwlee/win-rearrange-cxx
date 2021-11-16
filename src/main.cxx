#include "Handler.hxx"
#include "Config.hxx"

#include <iostream>

#ifdef __unix__
#include <unistd.h>
#define ISATTY(X) isatty(X)
#else
#include <io.h>
#define ISATTY(X) _isatty(X)
#endif

int main(int argc, char** argv) 
{
    // Load config from file
#ifdef __unix__
    Config config = Config::loadFromFile("unix_config.xml"); 
#else
    Config config = Config::loadFromFile("win_config.xml"); 
#endif
    // Initialize handler for processing
    Handler handle(config);
    handle.start();
    // Run until exit is requested
    while (true)
    {
        // Check if TTY 
        if (ISATTY(fileno(stdin)))
        {
            std::string input;
            // Block until input is given
            std::cin >> input;
            // Stop if exit is entered
            if (input == "exit")
            {
                handle.stop();
                break;
            }
        }
        else
        {
            // Sleep if non TTY
            std::this_thread::sleep_for(std::chrono::hours(24));
        }
    }
}
