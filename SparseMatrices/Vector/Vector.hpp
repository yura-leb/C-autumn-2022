#ifndef VECTOR_HPP
#define VECTOR_HPP

// #include "Exceptions"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    std::map<uint64_t, T> dictionary;
    double eps;
    uint64_t len;
public:

    Vector() {
        dictionary = std::map<uint64_t, T>();
        eps = 0.000000001;
        len = 0;
    }

    Vector(const int64_t value, uint64_t len) {
        dictionary = std::map<uint64_t, T>();
        if (value) {
            for (size_t i; i < len; ++i) {
                dictionary[i] = value;
            }
        }
        eps = 0.000000001;
        this->len = len;
    }

    Vector(const Vector& vec) {
        dictionary = vec.dictionary;
        eps = vec.eps;
        len = vec.len;
    }

    Vector(const std::map<uint64_t, T>& dictionary, double eps, uint64_t len) {
        this->dictionary = dictionary;
        this->eps = eps;
        this->len = len;
    }

    Vector(std::string fname) {
        dictionary = std::map<uint64_t, T>();
        eps = 0.000000001;
        std::string line, word, first = "", second = "", type = "";
        uint64_t coord;
        bool is_complex = false;
        std::ifstream input (fname);
        if (input.is_open())
        {
            while ( getline (input,line) )
            {
                first = "";
                second = "";
                std::istringstream iss(line);

                do {
                    iss >> word;
                    if (word == "vector") {
                        iss >> type;
                        iss >> word;
                        len = std::stoi(word);
                        break;
                    } else if (word[0] == '#') {
                        break;
                    } else {
                        coord = std::stoi(word);
                        iss >> word;
                        for (auto letter : word) {
                            if ('0' <= letter && letter <= '9' || letter == '.') {
                                second += letter;
                            } else if (letter == '/' || letter == ',') {
                                first = second;
                                second = "";
                            } else if (letter == '\n' || letter == '#') {
                                break;
                            }
                        }
                        switch (type[0]) {
                        case 'r':
                            if (first != "") {
                                dictionary[coord] = T(first, second);
                            } else {
                                dictionary[coord] = T(second, std::string("1"));
                            }
                            break;
                        case 'c':
                            if (first.find('.')) {
                                if (second.find('.'))
                                    dictionary[coord] = T(std::stod(first), std::stod(second));
                                else
                                    dictionary[coord] = T(std::stod(first), std::stoi(second));
                            } else {
                                if (second.find('.'))
                                    dictionary[coord] = T(std::stoi(first), std::stod(second));
                                else
                                    dictionary[coord] = T(std::stoi(first), std::stoi(second));
                            }
                            break;
                        case 'b':
                            dictionary[coord] = bool(std::stoi(second));

                        }
                        break;
                    }
                } while (iss);
            }
            input.close();
        }
    }
   
    bool is_zero(T num) {
        return -eps < num && num < eps;
    }

    void set_len(uint64_t len) {
        this->len = len;
    }

    T operator()(uint64_t i) {
        try {
            if (i >= len)
                throw "std::out_of_range";
            else
                return dictionary.at(i);
        } catch(const char *) {
            return T(0);
        } catch(std::out_of_range e) {
            std::cout << "ERROR" << std::endl;
        } catch (std::exception) {

        }
        return T(0);
    }

    const Vector& operator+(const Vector& right) const {
        Vector res = *this;
        for (auto const& elem : right.dictionary) {
            res[elem.first] += elem.second;
        }
        return res;
    }

    const Vector& operator-(const Vector& right) const {
        Vector res = *this;
        for (auto const& elem : right.dictionary) {
            res[elem.first] -= elem.second;
        }
        return res;
    }
    
    template<typename NUM>
    friend const Vector operator * (const Vector& left, const NUM& right) {
        Vector res = left;
        for (auto const & elem : left.dictionary) {
            res.dictionary[elem.first] = elem.second * right;
        }
        return res;
    }

    template<typename NUM>
    friend const Vector operator * (const NUM& left, const Vector& right) {
        return right * left;
    }

    template<typename NUM>
    friend const Vector operator / (const Vector& left, const NUM& right) {
        Vector res = left;
        for (auto const & elem : left.dictionary) {
            res.dictionary[elem.first] = elem.second / right;
        }
        return res;
    }

    std::string to_string() const {
        std::string res = "";
        for (auto elem : dictionary) {
            res += elem.second.to_string() + " ";

        }
        return res;
    }

    friend std::ostream & operator<<(std::ostream & str, const Vector<T> & number) {
        str << number.to_string();
        return str;
    }

};

#endif