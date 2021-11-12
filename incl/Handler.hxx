#ifndef HXX_HANDLER
#define HXX_HANDLER

#include <atomic>
#include <thread>
#include "Config.hxx"
#include "Command.hxx"

class Handler 
{
  public:
    Handler(Config& config);

    void start();

    void stop();
  
  private:
    std::atomic_bool m_stop;
    Config& m_config;
    std::unique_ptr<std::thread> m_thread;
    std::vector<Command*> m_commands;

#ifdef __unix__
    void runUnix();
#else
    void runWin32();
#endif
};

#endif
