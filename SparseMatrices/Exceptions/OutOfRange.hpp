#ifndef OUT_OF_RANGE_HPP
#define OUT_OF_RANGE_HPP

#include <exception>
#include <string>

class OutOfRange : public std::exception {
    std::string message;
    std::string len;
public:
    OutOfRange(std::string msg, std::string length = std::string()) {
        message = msg;
        this->len = length;
    }

    friend std::ostream & operator<<(std::ostream & str, const OutOfRange & error) {
        str << error.message;
        if (error.len != "") {
            str << std::string(" ") << error.len;
        }
        return str;
    }
};

#endif
