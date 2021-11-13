#include <iostream>
#ifdef __unix__
#include <unistd.h>
#endif
#include "Handler.hxx"
#include "Config.hxx"

#ifdef __unix__
#define ISATTY(X) isatty(X)
#else
#define ISATTY(X) _isatty(X)
#endif

int main(int argc, char** argv) 
{
  // Load config from file
  Config config = Config::loadFromFile("config.xml"); 
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
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  }
}
