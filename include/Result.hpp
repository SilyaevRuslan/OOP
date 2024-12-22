#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>

class Result {
public: 
    Result(std::string _message, bool success, bool allShipsAreDestroyed, int shipsDestroyed, bool hit)
        : _message(_message), _success(success), _allShipsAreDestroyed(allShipsAreDestroyed), _shipsDestroyed(shipsDestroyed), _hit(hit) {};
    std::string Message() {return _message;};
    bool Success() {return _success;};
    // Retruns amount of ships destroyed
    int ShipsDestroyed() {return _shipsDestroyed;};
    bool AllShipsDestroyed() {return _allShipsAreDestroyed;};
    bool Hit() {return _hit;};
private:
    std::string _message;
    bool _success;
    int _shipsDestroyed;
    bool _allShipsAreDestroyed;
    bool _hit;
};

#endif
 