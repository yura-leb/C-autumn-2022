#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "WrongInput.hpp"
#include "OutOfRange.hpp"
#include "DifferentSizes.hpp"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;  
    }
};


template <typename T>
class Matrix {
private:

    
    std::unordered_map<std::pair<uint64_t, uint64_t>, T, pair_hash> matrix_;
    inline static double eps = 0.0000000001;
    uint64_t hight;
    uint64_t width;

public:

    Matrix() {
        hight = 0;
        width = 0;
    }

    Matrix(uint64_t hight, uint64_t width) {
        this->hight = hight;
        this->width = width;
        for (size_t i=0; i < hight; ++i) {
            matrix_[{i, i}] = T(1);
        }
    }

    Matrix(const int64_t value, const uint64_t hight, const uint64_t width) {
        if (bool(value)) {
            for (size_t i = 0; i < hight; ++i) {
                for (size_t j = 0; j < width; j++) {
                    std::cout << i << j << std::endl;
                    matrix_[{i, j}] = T(value);
                }
            }
        }
        this->hight = hight;
        this->width = width;
    }

    Matrix(const Matrix& right) {
        matrix_ = right.matrix_;
        hight = right.hight;
        width = right.width;
    }

    Matrix(const std::unordered_map<std::pair<uint64_t, uint64_t>, T, pair_hash>& matrix, uint64_t hight, uint64_t width) {
        this->matrix_ = matrix;
        this->hight = hight;
        this->width = width;
    }

    Matrix(std::string fname) {
        std::string line, word, first = "", second = "", type = "";
        std::pair<uint64_t, uint64_t> coord;
        bool is_complex = false;
        bool comment = false;
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
                    if (word == "matrix") {
                        iss >> type;
                        iss >> word;
                        hight = std::stoi(word);
                        iss >> word;
                        width = std::stoi(word);
                        break;
                    } else if (word[0] == '#') {
                        break;
                    } else {
                        coord.first = std::stoi(word) - 1;
                        iss >> word;
                        coord.second = std::stoi(word) - 1;
                        while (!iss.eof()) {
                            iss >> word;
                            comment = false;
                            for (auto letter : word) {
                                if ('0' <= letter && letter <= '9' || letter == '.' || letter == '-') {
                                    second += letter;
                                } else if (letter == '/' || letter == ',') {
                                    first = second;
                                    second = "";
                                } else if (letter == '#') {
                                    break;
                                }
                            }
                        }
                        switch (type[0]) {
                        case 'r':
                            if (first != "") {
                                matrix_[coord] = T(first, second);
                            } else {
                                matrix_[coord] = T(second);
                            }
                            break;
                        case 'c':
                            if (first.find('.') != -1) {
                                if (second.find('.') != -1)
                                    matrix_[coord] = T(std::stod(first), std::stod(second));
                                else
                                    matrix_[coord] = T(std::stod(first), std::stoi(second));
                            } else {
                                if (second.find('.') != -1) {
                                    matrix_[coord] = T(std::stoi(first), std::stod(second));
                                }
                                else
                                    matrix_[coord] = T(std::stoi(first), std::stoi(second));
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

    Matrix operator+(const Matrix& right) const {
        if (hight != right.hight) {
            throw DifferentSizes("Different hights when add matrices:", std::to_string(hight), std::to_string(right.hight));
        } else if (width != right.width) {
            throw DifferentSizes("Different widths when add matrices:", std::to_string(width), std::to_string(right.width));
        }

        Matrix res = *this;

        for (auto kv : right.matrix_) {
            res.matrix_[kv.first] += kv.second;
            if (res.matrix_[kv.first].is_zero(eps)) {
                res.matrix_.erase(kv.first);
            }
        }
        return res;
    }

    Matrix operator-(const Matrix& right) const {
        if (hight != right.hight) {
            throw DifferentSizes("Different hights when substract matrices:", std::to_string(hight), std::to_string(right.hight));
        } else if (width != right.width) {
            throw DifferentSizes("Different widths when substract matrices:", std::to_string(width), std::to_string(right.width));
        }

        Matrix res = *this;

        for (auto kv : right.matrix_) {
            res.matrix_[kv.first] -= kv.second;
            if (res.matrix_[kv.first].is_zero(eps)) {
                res.matrix_.erase(kv.first);
            }
        }
        return res;
    }

    Matrix operator*(const Matrix& right) const {
        if (width != right.hight) {
            throw DifferentSizes("Different hights when multiply matrices:", std::to_string(width), std::to_string(right.hight));
        }

        Matrix res;
        res.hight = hight;
        res.width = right.width;

        std::set<uint64_t> non_zero_lines;
        std::set<uint64_t> non_zero_columns;

        for (auto kv : matrix_) {
            non_zero_lines.insert(kv.first.first);
        }
        for (auto kv : matrix_) {
            non_zero_columns.insert(kv.first.second);
        }
        
        for (auto i : non_zero_lines) {
            for (auto j : non_zero_columns) {
                res.matrix_[{i, j}] = T(0);
                for (size_t k=0; k < width; ++k) {
                    res.matrix_[{i, j}] += (*this)(i, k) * right(k, j);
                }
                if (res(i, j).is_zero(eps))
                    res.matrix_.erase({i, j});
            }
        }
        
        return res;
    }

    Matrix operator-() const {
        Matrix res(*this);
        for (auto kv : matrix_) {
            res.matrix_[kv.first] = -kv.second;
        }
        return res;
    }

    const Matrix& operator=(const Matrix& right) {
        matrix_ = right.matrix_;
        hight = right.hight;
        width = right.width;
    }
    
    std::string to_string() const {
        std::string res = "";
        for (size_t i=0; i < hight; ++i) {
            for (size_t j=0; j < width; ++j) {
                res += (*this)(i, j).to_string() + " ";
            }
            res += "\n";

        }
        return res;
    }

    friend std::ostream & operator<<(std::ostream & str, const Matrix & number) {
        str << number.to_string();
        return str;
    }

    T operator() (const uint64_t i, const uint64_t j) const {
        try {
            if (i >= hight)
                throw OutOfRange("Matrix higth out of range");
            if (j >= width)
                throw OutOfRange("Matrix width out of range");
            return matrix_.at({i, j});
        } catch (std::out_of_range) {
            return T(0);
        } 
        return T(0);
    }
};

#endif
