#include "CLICommandReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

CLICommandReader::CLICommandReader(const std::string& configPath) {
    if (!loadConfig(configPath)) {
        // Если не удалось загрузить конфигурацию, установим значения по умолчанию
        commandMap = {
            {"attack", static_cast<CommandType>(0)},
            {"ability", static_cast<CommandType>(1)},
            {"load", static_cast<CommandType>(2)},
            {"save", static_cast<CommandType>(3)},
            {"preview", static_cast<CommandType>(4)}
        };
        std::cerr << "Failed to load config file: " << configPath << ". Using default commands." << std::endl;
    }
}

bool CLICommandReader::loadConfig(const std::string& configPath) {
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        return false;
    }

    commandMap.clear();
    std::string commandName;
    int commandIndex = 0;
     while (std::getline(configFile, commandName)) {
        trim(commandName);
        if (commandName.empty()) continue;
            switch (commandIndex) {
            case 0: commandMap[commandName] = static_cast<CommandType>(0);
                break;
            case 1: commandMap[commandName] = static_cast<CommandType>(1);
                break;
            case 2: commandMap[commandName] = static_cast<CommandType>(2);
                 break;
            case 3: commandMap[commandName] = static_cast<CommandType>(3);
                 break;
            case 4: commandMap[commandName] = static_cast<CommandType>(4);
                 break;
             default:
                std::cerr << "Too many command config names" << std::endl;
                return false;
            }
            commandIndex++;
        }
    configFile.close();
    return commandIndex == 5;
}


void CLICommandReader::trim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

Command CLICommandReader::parseCommand(const std::string& input) {
    std::string trimmedInput = input;
    trim(trimmedInput);
    std::istringstream iss(trimmedInput);
    std::string commandName;
    iss >> commandName;
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    auto it = commandMap.find(commandName);
    if (it == commandMap.end()) {
         throw InvalidCommandException("Invalid command: " + commandName);
    }
    
    switch (it->second) {
        case static_cast<CommandType>(0):
            return parseAttack(args);
        case static_cast<CommandType>(1):
            return parseAbility(args);
        case static_cast<CommandType>(2):
            return parseLoad(args);
        case static_cast<CommandType>(3):
            return parseSave(args);
        case static_cast<CommandType>(4):
            return parsePreviewAbility(args);
        default:
             throw InvalidCommandException("Invalid command: " + commandName);
    }

}

Command CLICommandReader::parseAttack(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        throw InvalidCommandException("Invalid number of arguments for attack command. Expected 2, but got " + std::to_string(args.size()));
    }
    try {
        int x = std::stoi(args[0]);
        int y = std::stoi(args[1]);
        return Command(static_cast<CommandType>(0), x, y);
    } catch (const std::invalid_argument& e) {
        throw InvalidCommandException("Invalid arguments for attack command. Coordinates must be integers");
    }
}

Command CLICommandReader::parseAbility(const std::vector<std::string>& args) {
   if (args.empty()) {
        return Command(static_cast<CommandType>(1));
    }
     if (args.size() != 2) {
        throw InvalidCommandException("Invalid number of arguments for ability command. Expected 0 or 2, but got " + std::to_string(args.size()));
    }
    try {
        int x = std::stoi(args[0]);
        int y = std::stoi(args[1]);
        return Command(static_cast<CommandType>(1), x, y);
    } catch (const std::invalid_argument& e) {
        throw InvalidCommandException("Invalid arguments for ability command. Coordinates must be integers");
    }
}

Command CLICommandReader::parseLoad(const std::vector<std::string>& args) {
    if (!args.empty()) {
        throw InvalidCommandException("Invalid number of arguments for load command. Expected 0, but got " + std::to_string(args.size()));
    }
    return Command(static_cast<CommandType>(2));
}

Command CLICommandReader::parseSave(const std::vector<std::string>& args) {
    if (!args.empty()) {
         throw InvalidCommandException("Invalid number of arguments for save command. Expected 0, but got " + std::to_string(args.size()));
    }
    return Command(static_cast<CommandType>(3));
}

Command CLICommandReader::parsePreviewAbility(const std::vector<std::string>& args) {
     if (!args.empty()) {
         throw InvalidCommandException("Invalid number of arguments for preview command. Expected 0, but got " + std::to_string(args.size()));
    }
    return Command(static_cast<CommandType>(4));
}