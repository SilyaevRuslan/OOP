#include "Context.hpp"
#include "Exceptions.hpp"

std::string Context::GetParam(std::string key){
    auto it = params.find(key);
    if (it != params.end()) {
        return it->second;
    }
    return "";
}

void Context::SetParam(std::string key, std::string value){
    params[key] = value;
}