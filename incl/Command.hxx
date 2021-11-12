#ifndef HXX_COMMAND
#define HXX_COMMAND

#include <string>

class Command 
{
  public:
    Command(std::string path, std::string command);

    void run();
     
    bool isActive();
     
    void kill();

  private:
    std::string m_path;
    std::string m_command;
#ifdef __unix__
    pid_t m_pid;
#endif
};

#endif
