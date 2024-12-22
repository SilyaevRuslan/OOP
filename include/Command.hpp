#ifndef COMMAND_HPP
#define COMMAND_HPP

enum class CommandType {
    Attack,
    Ability,
    Load,
    Save,
    PreviewAbility,
    Invalid // Для обозначения некорректной команды
};

class Command {
public:
    CommandType type;
    int x;
    int y;
    Command(CommandType type, int x = -1, int y = -1) : type(type), x(x), y(y) {};
    
};

#endif