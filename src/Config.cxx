#include "Config.hxx"
#include "utils.hxx"

#include <iostream>
#include <fstream>
#include <ostream>
#include <algorithm>

Config::Config()
{
} 

Config Config::loadFromFile(std::string filename)
{
    Config config;
    config.load(filename);
    return config;
}

bool operator<(const Config::RuleDefinition& val1, const Config::RuleDefinition& val2)
{
    return val1.priority > val2.priority;
}

void Config::load(std::string filename)
{
    // Read XML
    std::ifstream is(filename, std::ifstream::in);
    cereal::XMLInputArchive ar(is);
    ar(cereal::make_nvp("command_definitions", m_commands));
    ar(cereal::make_nvp("profiles", m_profiles));
    for (auto iter = m_profiles.begin(); iter != m_profiles.end(); ++iter)
    {  
        // Sort based on priority
        std::stable_sort((*iter).rules.begin(), (*iter).rules.end());
    }
}

void Config::save(std::string filename)
{
    // Print XML into file
    std::ofstream os(filename, std::ios::out);
    cereal::XMLOutputArchive archive(os);
    archive(cereal::make_nvp("command_definitions", m_commands));
    archive(cereal::make_nvp("profiles", m_profiles));
}

std::vector<Config::CommandDefinition> const& Config::getCommands()
{
    return m_commands;
}

std::vector<Config::RuleDefinition> const& Config::getRules(std::string profile)
{
    static std::vector<Config::RuleDefinition> const vec;
    for (auto iter = m_profiles.begin(); iter != m_profiles.end(); ++iter)
    {  
        if ((*iter).name == profile)
        {
            return (*iter).rules;
        }
    }
    return vec;
}

