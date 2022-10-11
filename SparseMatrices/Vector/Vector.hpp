#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "WrongInput.hpp"
#include "OutOfRange.hpp"
#include "DifferentSizes.hpp"
#include "BadCast.hpp"
#include "Matrix.hpp"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

template <typename T>
class Vector;

template <typename T>
class Vector {
private:
    /**
     * container of elements with coorddinates.
     */
    std::map<uint64_t, T> dictionary;

    /**
     * Zero approximator.
     */
    inline static double eps = 0.0000000001;

    /**
     * Length of vector.
     */
    uint64_t len;
public:
    /**
     * Default constructor.
     */
    Vector() {
        dictionary = std::map<uint64_t, T>();
        len = 0;
    }

    /**
     * Constructor from value and length. Initializes vector with every element = value and length = len. 
     * 
     * @param  value : value of every element.
     * @param  len   : length of vector.
     */
    Vector(const int64_t value, uint64_t len) {
        dictionary = std::map<uint64_t, T>();
        if (value) {
            for (size_t i; i < len; ++i) {
                dictionary[i] = value;
            }
        }
        this->len = len;
    }
    
    /**
     * Copy constructor. 
     * 
     * @param  vec : other vector.
     */
    Vector(const Vector& vec) {
        dictionary = vec.dictionary;
        len = vec.len;
    }
    
    Vector(MatrixProxy<T> mp) {
        if (mp.is_vector) {
            if (mp.r2 - mp.r1 == 1) {
                len = mp.c2 - mp.c1;
                for (size_t i=mp.c1; i < mp.c2; i++) {
                    if (mp.matrix_ref.contains({mp.r1, i})) {
                        dictionary[i] = mp.matrix_ref[{mp.r1, i}];
                    }
                }
            } else {
                len = mp.r2 - mp.r1;
                for (size_t i=mp.r1; i < mp.r2; i++) {
                    if (mp.matrix_ref.contains({i, mp.c1})) {
                        dictionary[i] = mp.matrix_ref[{i, mp.c1}];
                    }
                }
            }

        } else {
            throw BadCast("Wrong cast slice to vector");
        }
    }

/**
     * Multiply matrix on vector.
     * 
     * @param  right      : vector.
     * @return {Vector}   : product matrix * vector.
     */
    Vector<T> operator*(Matrix<T>& right) const {
        if (len != right.get_hight()) {
            throw DifferentSizes("Different hights when multiply vector on matrix: ", std::to_string(len), std::to_string(right.get_hight()));
        }
        Vector<T> res;
        res.len = right.get_width();

        std::set<uint64_t> non_zero_columns;

        for (auto kv : *(right.get_matrix_pointer())) {
            non_zero_columns.insert(kv.first.second);
        }
        
        for (auto i : non_zero_columns) {
            res.dictionary[i] = T(0);
            for (auto j=0; j < len; ++j) {
                std::cout << (*this)(j+1) << " " << right(j+1, i+1) << std::endl;
                res.dictionary[i] += (*this)(j+1) * right(j+1, i+1); // operator () works with i+1
            }
            std::cout << "res " << res(i+1) << std::endl;
            if (res(i+1).is_zero(eps))
                res.dictionary.erase(i);
        }
        
        return res;
    }
    

    /**
     * Constructor from map. 
     * 
     * @param  dictionary : map with coordinates and values.
     * @param  len        : vector length.
     */
    Vector(const std::map<uint64_t, T>& dictionary, uint64_t len) {
        this->dictionary = dictionary;
        this->len = len;
    }
    
    /**
     * Constructor from file. 
     * 
     * @param  fname : filename to construct from.
     */
    Vector(std::string fname) {
        dictionary = std::map<uint64_t, T>();
        std::string line, word, first = "", second = "", type = "";
        uint64_t coord;
        bool comment = false;
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
                        coord = std::stoi(word) - 1;
                        if (coord < 0 || len <= coord) {
                            throw OutOfRange("Vector hight coordinate out of range");
                        }
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
                                dictionary[coord] = T(first, second);
                            } else {
                                dictionary[coord] = T(second);
                            }
                            break;
                        case 'c':
                            if (first.find('.') != -1) {
                                if (second.find('.') != -1)
                                    dictionary[coord] = T(std::stod(first), std::stod(second));
                                else
                                    dictionary[coord] = T(std::stod(first), std::stoi(second));
                            } else {
                                if (second.find('.') != -1) {
                                    dictionary[coord] = T(std::stoi(first), std::stod(second));
                                }
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
        } else {
            throw FileNotFound("Vector constructor: not found", fname);
        }
    }
   
    
    /**
     * Operator [].
     * 
     * @param  i    : coordinate.
     * @return {T}  : reference to element.
     */
    T& operator[](uint64_t i) {
        if (i <= 0 || len < i)
            throw OutOfRange("Out of range. Coordinate is more than", std::to_string(len));
        return dictionary[i];
    }
    /**
     * Length setter.
     * 
     * @param  len : vector length.
     */
    void set_len(uint64_t len) {
        this->len = len;
    }

    uint64_t get_len() const {
        return len;
    }
    /**
     * Get value to read.
     * 
     * @param  i    : coordinate.
     * @return {T}  : element.
     */
    const T operator()(uint64_t i) const {
        try {
            if (i <= 0 || len < i)
                throw OutOfRange("Out of range. Coordinate is more than", std::to_string(len));
            else
                return dictionary.at(i-1);
        } catch(std::out_of_range e) {
            return T(0);
        }
        return T(0);
    }
    
    /**
     * Add.
     * 
     * @param  right     : other vector.
     * @return {Vector}  : result of operation.
     */
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
    /**
     * Substract.
     * 
     * @param  right     : other vector.
     * @return {Vector}  : result of operation.
     */
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
    /**
     * Multiply vector on number.
     * 
     * @param  left       : vector to multiply. 
     * @param  right      : number to multiply.
     * @return {Vector}   : vector with every element multiplied on number. 
     */
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
    /**
     * Multiply number on vector.
     * 
     * @param  left       : number to multiply.
     * @param  right      : vector to multiply. 
     * @return {Vector}   : vector with every element multiplied on number.
     */
    friend const Vector operator * (const NUM& left, const Vector& right) {
        return right * left;
    }

    template<typename NUM>
    /**
     * Divide vector on number.
     * 
     * @param  left      : vector to divide.
     * @param  right     : number to diide.
     * @return {Vector}  : vector with every element divided on number.
     */
    friend const Vector operator / (const Vector& left, const NUM& right) {
        Vector res = left;
        for (auto const & elem : left.dictionary) {
            res.dictionary[elem.first] = elem.second / right;
            if (res.dictionary[elem.first].is_zero(eps))
                res.dictionary.erase(elem.first);
        }
        return res;
    }

    /**
     * Convert vector to string.
     * 
     * @return {std::string}  : vector in string representation.
     */
    std::string to_string() const {
        std::string res = "";
        for (uint64_t i=1; i <= len; ++i) {
            res += (*this)(i).to_string() + " ";
        }
        return res;
    }

    /**
     * Print vector to stream.
     * 
     * @param  str             : stream to print vector.
     * @param  vec             : vector to print.
     * @return {std::ostream}  : stream.
     */
    friend std::ostream & operator<<(std::ostream & str, const Vector<T> & vec) {
        str << vec.to_string();
        return str;
    }

};

#endif