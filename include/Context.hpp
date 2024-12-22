#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <string>
#include <map>

class Context {
public:
    Context(){};
    // Returns parameter, if key exists. Else ""
    std::string GetParam(std::string key);
    // Sets parameter
    void SetParam(std::string key, std::string value);
private:
    std::map<std::string, std::string> params;
};

#endif

