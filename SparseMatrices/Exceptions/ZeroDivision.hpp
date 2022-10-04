#include <exception>
#include <string>

class ZeroDivision : public std::exception {
public:
    std::string message;
    std::string left;
    std::string right;
    ZeroDivision(std::string message, std::string left = std::string(), std::string right = std::string()) { 
        this->left = left; 
        this->right = right; 
        this->message = message;
    }

    friend std::ostream & operator<<(std::ostream & str, const ZeroDivision & error) {
        str << error.message;
        if (error.left != "") {
            str << " " << error.left << " " << error.right;
        }
        return str;
    }
};
