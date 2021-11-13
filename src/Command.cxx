#include "Command.hxx"
#include "utils.hxx"

#ifdef __unix__
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#else
#include <windows.h>
#endif

Command::Command(std::string path, std::string command)
  : m_path(path)
  , m_command(command)
#ifdef __unix__
  , m_pid(0)
#else
  , m_startupInfo()
  , m_pinfo()
#endif
{
  #ifdef __unix__
  #else
  ZeroMemory(&m_startupInfo, sizeof(m_startupInfo));
  m_startupInfo.cb = sizeof(m_startupInfo);
  ZeroMemory(&m_pinfo, sizeof(m_pinfo));
  #endif
}

void Command::run() 
{
#ifdef __unix__
  m_pid = fork();
  if (m_pid == 0)
  {
    if(execlp((m_path + "/" + m_command).c_str(), m_command.c_str(), NULL) < 0)
    {
      LOG_ERROR("Starting " << m_path << "/" << m_command << " failed.");
    }
  }
#else
  LPSTR fullpath = strdup((m_path + "\\" + m_command).c_str());
  if (!CreateProcess(
    nullptr,
    fullpath,
    nullptr,
    nullptr,
    false,
    0,
    nullptr,
    nullptr,
    &m_startupInfo,
    &m_pinfo
  )) 
  {
    LOG_ERROR("Starting " << fullpath << " failed.");
  }
  free(fullpath);
#endif
}

void Command::kill()
{
#ifdef __unix__
  ::kill(m_pid, SIGKILL);
  int status;
  waitpid(m_pid, &status, 0);
#else
  TerminateProcess(m_pinfo.hProcess, 1);
  CloseHandle(m_pinfo.hProcess);
  CloseHandle(m_pinfo.hThread);
#endif
}

bool Command::isActive()
{
#ifdef __unix__
  int status = 0;
  return waitpid(m_pid, &status, WNOHANG) >= 0;
#else
  return WaitForSingleObject(m_pinfo.hProcess, 0) == WAIT_TIMEOUT;
#endif
}
