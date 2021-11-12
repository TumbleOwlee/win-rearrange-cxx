#include "Command.hxx"
#ifdef __unix__
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#endif
#include "utils.hxx"

Command::Command(std::string path, std::string command)
  : m_path(path)
  , m_command(command)
#ifdef __unix__
  , m_pid(0)
#endif
{
}

void Command::run() 
{
#ifdef __unix__
  m_pid = fork();
  if (m_pid == 0)
  {
    execlp( 
      (m_path + "/" + m_command).c_str(), 
      m_command.c_str(),
      NULL
    );
  }
#else
#endif
}

void Command::kill()
{
#ifdef __unix__
  ::kill(m_pid, SIGKILL);
#else
#endif
}

bool Command::isActive()
{
#ifdef __unix__
  int status = 0;
  return waitpid(m_pid, &status, WNOHANG) > 0;
#else
#endif
}
