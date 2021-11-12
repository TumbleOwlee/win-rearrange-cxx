#include "Handler.hxx"
#include "XSystem.hxx"
#include "XWindow.hxx"
#include <functional>
#include <regex>
#include "utils.hxx"
#include "Command.hxx"

Handler::Handler(Config& config)
  : m_stop(false)
  , m_config(config)
{
}

void Handler::start()
{
  // Start applications
  auto commands = m_config.getCommands();
  for (auto iter = commands.begin(); iter != commands.end(); ++iter)
  {
    auto cmd = new Command((*iter).path, (*iter).command);
    cmd->run();
    m_commands.push_back(cmd);
  }
#ifdef __unix__
  m_thread.reset(new std::thread(std::function<void()>(std::bind(&Handler::runUnix, this))));
#else
  m_thread.reset(new std::thread(std::function<void()>(std::bind(&Handler::runWin32, this))));
#endif
}

void Handler::stop()
{
  // Initialize handler stop
  m_stop = true;
  // Stop all commands
  for (auto iter = m_commands.begin(); iter != m_commands.end(); ++iter)
  {
    if((*iter)->isActive())
    {
      (*iter)->kill();
      delete (*iter);
    }
  }
  // Wait for thread finish
  (*m_thread).join();
}

#ifdef __unix__
void Handler::runUnix()
{
  // Create basic system
  XSystem system;
  // Retrieve rules
  auto rules = m_config.getRules("default");
  // Start commands
  std::vector<Command*> startedCmds;
  // Loop until stopped
  while(!m_stop) 
  {
    std::vector<XWindow*> windows;
    auto stack = system.getWindowStack();
    for (auto rule = rules.begin(); rule != rules.end(); ++rule)
    {
      for (auto iter = stack.begin(); iter != stack.end(); ++iter)
      {
        if (std::find(windows.begin(), windows.end(), &(*iter)) != windows.end())
        {
          continue;
        }
        std::cmatch match;
        std::regex re((*rule).regex);
        // Check if rule applies
        if (std::regex_match((*iter).getName().c_str(), match, re))
        {
          // Move window
          (*iter).moveAndResize((*rule).left, (*rule).top, (*rule).right - (*rule).left, (*rule).bottom - (*rule).top);
          windows.push_back(&(*iter));
        }
      }
    }
    // Restack windows
    for (auto iter = windows.end(); iter != windows.begin(); --iter)
    {
      (*(iter - 1))->raise();
    }
    // Sleep 
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
}
#else
void Handler::runWin32()
{

}
#endif
