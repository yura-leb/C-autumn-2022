#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "WrongInput.hpp"
#include "OutOfRange.hpp"
#include "DifferentSizes.hpp"
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
    inline static double eps = 0.0000000001;
    uint64_t len;
public:

    Vector() {
        dictionary = std::map<uint64_t, T>();
        len = 0;
    }

    Vector(const int64_t value, uint64_t len) {
        dictionary = std::map<uint64_t, T>();
        if (value) {
            for (size_t i; i < len; ++i) {
                dictionary[i] = value;
            }
        }
        this->len = len;
    }

    Vector(const Vector& vec) {
        dictionary = vec.dictionary;
        len = vec.len;
    }

    Vector(const std::map<uint64_t, T>& dictionary, uint64_t len) {
        this->dictionary = dictionary;
        this->len = len;
    }

    Vector(std::string fname) {
        dictionary = std::map<uint64_t, T>();
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
                        try {
                            coord = std::stoi(word) - 1;
                        } catch (std::invalid_argument) {
                            throw WrongInput("Wrong vector coordinate input");
                        }
                        iss >> word;
                        for (auto letter : word) {
                            if ('0' <= letter && letter <= '9' || letter == '.' || letter == '-') {
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
                throw OutOfRange("Out of range. Coordinate is more than", std::to_string(len));
            else
                return dictionary.at(i);
        } catch(std::out_of_range e) {
            return T(0);
        }
        return T(0);
    }

    Vector operator+(const Vector& right) const {
        if (len != right.len)
            throw DifferentSizes("Different sizes when add vectors:", std::to_string(len), std::to_string(right.len));
        Vector res = *this;
        for (auto const& elem : right.dictionary) {
            res.dictionary[elem.first] += elem.second;
            if (res.dictionary[elem.first].is_zero(eps))
                res.dictionary.erase(elem.first);
        }
        return res;
    }

    Vector operator-(const Vector& right) const {
        if (len != right.len)
            throw DifferentSizes("Different sizes when substract vectors:", std::to_string(len), std::to_string(right.len));
        Vector res = *this;
        for (auto const& elem : right.dictionary) {
            res[elem.first] -= elem.second;
            if (res.dictionary[elem.first].is_zero(eps))
                res.dictionary.erase(elem.first);
        }
        return res;
    }
    
    template<typename NUM>
    friend const Vector operator * (const Vector& left, const NUM& right) {
        Vector res = left;
        for (auto const & elem : left.dictionary) {
            res.dictionary[elem.first] = elem.second * right;
            if (res.dictionary[elem.first].is_zero(eps))
                res.dictionary.erase(elem.first);
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
            if (res.dictionary[elem.first].is_zero(eps))
                res.dictionary.erase(elem.first);
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