#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <stdexcept>
#include <string>

class InvalidCommandException : public std::runtime_error {
public:
    InvalidCommandException(const std::string& message) : std::runtime_error(message) {}
};

class AbilityException : public std::exception {
public:
    virtual const char* what() const throw() = 0;
};

class NoAbilitiesException : public AbilityException {
public:
    const char* what() const throw() {
        return "No abilities are available!";
    }
};

class ShipPlacementException : public std::exception {
public:
    const char* what() const throw() {
        return "It is not possible to place a ship here!";
    }
};

class OutOfBoundsException : public std::exception {
public:
    const char* what() const throw() {
        return "Off-the-field attack!";
    }
};

class AttackingDestroyedSegmentException : public std::exception {
public:
    const char* what() const throw() {
        return "Segment is already destroyed!";
    }
};

class EmptyCellAttackException : public std::exception {
    const char* what() const throw() {
        return "Can not attack an emply cell!";
    }
};

class UnableToOpenFileException : public std::exception {
    const char* what() const throw() {
        return "Unable to open the file!";
    }
};

#endif