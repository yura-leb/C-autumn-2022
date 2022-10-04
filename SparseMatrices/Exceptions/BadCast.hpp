#include <exception>
#include <string>

class BadCast : public std::exception {
private:
    std::string message;
public:
    BadCast(std::string msg) : message(msg) {}

    friend std::ostream & operator<<(std::ostream & str, const BadCast & error) {
        str << error.message;
        return str;
    }
};
