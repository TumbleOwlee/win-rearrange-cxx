#include "Handler.hxx"
#include "utils.hxx"
#include "Command.hxx"

#include <functional>
#include <regex>

#ifdef __unix__
#include "XSystem.hxx"
#include "XWindow.hxx"
#else
#include "WinSystem.hxx"
#include "WinWindow.hxx"
#endif

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
    m_thread.reset(new std::thread(std::function<void()>(std::bind(&Handler::run, this))));
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
        }
        delete (*iter);
    }
    // Wait for thread finish
    (*m_thread).join();
}

void Handler::run()
{
    // Create basic system
#ifdef __unix__
    XSystem system;
#else
    WinSystem system;
#endif
    // Retrieve rules
    auto rules = m_config.getRules("default");
    // Loop until stopped
    while(!m_stop) 
    {
#ifdef __unix__
        std::vector<XWindow*> windows;
#else
        std::vector<WinWindow*> windows;
#endif
        auto stack = system.getWindowStack();
        for (auto rule = rules.begin(); rule != rules.end(); ++rule)
        {
            bool applied = false;
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
                    applied = true;
                }
            }
            if (!applied)
            {
                LOG_ERROR("Rule '" << (*rule).regex << "' not applied. No window found.");
            }
        }
        // Restack windows
        system.applyOrder(windows);
        // Sleep 
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
