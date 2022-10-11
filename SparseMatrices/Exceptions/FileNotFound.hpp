#ifndef FILE_NOT_FOUND_HPP
#define FILE_NOT_FOUND_HPP

#include <exception>
#include <string>

class FileNotFound : public std::exception {
    std::string message;
    std::string fname;
public:
    FileNotFound(std::string msg, std::string fname = std::string()) {
        message = msg;
        this->fname = fname;
    }

    friend std::ostream & operator<<(std::ostream & str, const FileNotFound & error) {
        str << error.message;
        if (error.fname != "") {
            str << std::string(" ") << error.fname;
        }
        return str;
    }
};

#endif

