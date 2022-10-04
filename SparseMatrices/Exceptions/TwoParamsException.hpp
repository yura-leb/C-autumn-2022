#ifndef TWO_PARAMS_EXCEPTION_HPP
#define TWO_PARAMS_EXCEPTION_HPP

#include <exception>
#include <string>

class TwoParamsException : public std::exception {
public:
    std::string message;
    std::string left;
    std::string right;
    TwoParamsException(std::string message, std::string left = std::string(), std::string right = std::string()) { 
        this->left = left; 
        this->right = right; 
        this->message = message;
    }

    friend std::ostream & operator<<(std::ostream & str, const TwoParamsException & error) {
        str << error.message;
        if (error.left != "") {
            str << std::string(" ") << error.left << std::string(" ") << error.right;
        }
        return str;
    }
};

#endif
