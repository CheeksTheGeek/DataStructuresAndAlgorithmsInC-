#pragma once

#include <exception>
#include <string>

class IllegalException : public std::exception {
private:
    std::string message_{"illegal argument"};
public:
    inline explicit IllegalException(std::string message) : message_(std::move(message)) {}
    inline explicit IllegalException() = default;
    inline const char *what() const noexcept override{return message_.c_str();}
};