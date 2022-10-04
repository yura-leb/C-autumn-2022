#ifndef WRONG_INPUT_HPP
#define WRONG_INPUT_HPP

#include <exception>
#include <string>

class WrongInput : public std::exception {
    std::string message;
public:
    WrongInput(std::string msg) : message(msg){}

    friend std::ostream & operator<<(std::ostream & str, const WrongInput & error) {
        str << error.message;
        return str;
    }
};

#endif
