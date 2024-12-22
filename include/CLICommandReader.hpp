#ifndef CLICOMMANDREADER_HPP
#define CLICOMMANDREADER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Exceptions.hpp"
#include "Command.hpp"

class CLICommandReader {
public:
    CLICommandReader(const std::string& configPath = "commands.conf");
    Command parseCommand(const std::string& input);

private:
    Command parseAttack(const std::vector<std::string>& args);
    Command parseAbility(const std::vector<std::string>& args);
    Command parseLoad(const std::vector<std::string>& args);
    Command parseSave(const std::vector<std::string>& args);
    Command parsePreviewAbility(const std::vector<std::string>& args);
    void trim(std::string &str);
    bool loadConfig(const std::string& configPath);
    std::map<std::string, CommandType> commandMap;
};

#endif