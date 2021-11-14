#ifndef HXX_CONFIG
#define HXX_CONFIG

#include <cereal/archives/xml.hpp>
#include <cereal/types/vector.hpp>
#include <string>

class Config 
{
public:
    struct CommandDefinition
    {
        std::string path;
        std::string command;

        template<class Archive>
            void serialize(Archive& ar)
            {
                ar(
                        cereal::make_nvp("path", path), 
                        cereal::make_nvp("command", command)
                  );
            }
    };

    struct RuleDefinition
    {
        std::string regex;
        size_t priority;
        unsigned int left;
        unsigned int top;
        unsigned int right;
        unsigned int bottom;

        template<class Archive>
            void serialize(Archive& ar)
            {
                ar(
                        cereal::make_nvp("regex", regex), 
                        cereal::make_nvp("priority", priority), 
                        cereal::make_nvp("left", left), 
                        cereal::make_nvp("top", top), 
                        cereal::make_nvp("right", right), 
                        cereal::make_nvp("bottom", bottom)
                  );
            }
    };

    struct Profile
    {
        std::string name;
        std::vector<RuleDefinition> rules;

        template<class Archive>
            void serialize(Archive& ar)
            {
                ar(
                        cereal::make_nvp("name", name), 
                        cereal::make_nvp("rules", rules)
                  );
            }
    };

    Config();

    static Config loadFromFile(std::string filename);

    void load(std::string filename);

    void save(std::string filename);

    std::vector<CommandDefinition> const& getCommands();

    std::vector<RuleDefinition> const& getRules(std::string profile);

private:
    std::vector<CommandDefinition> m_commands;
    std::vector<Profile> m_profiles;
};

#endif
