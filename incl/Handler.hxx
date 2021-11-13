#ifndef HXX_HANDLER
#define HXX_HANDLER

#include "Config.hxx"
#include "Command.hxx"

#include <atomic>
#include <thread>

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

    void run();
};

#endif
