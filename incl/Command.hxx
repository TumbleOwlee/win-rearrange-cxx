#ifndef HXX_COMMAND
#define HXX_COMMAND

#include <string>

#ifdef __unix__
#else
#include <windows.h>
#endif

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
#else
    STARTUPINFO m_startupInfo;
    PROCESS_INFORMATION m_pinfo;
#endif
};

#endif
