#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "WrongInput.hpp"
#include "OutOfRange.hpp"
#include "DifferentSizes.hpp"
#include "FileNotFound.hpp"
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>
/**
 * Hash for unordered map in matrix. 
 */
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;  
    }
};

class Matrix_coords {
public:
    uint64_t r1_, c1_;
    uint64_t r2_, c2_;

    Matrix_coords(uint64_t r1, uint64_t c1, uint64_t r2, uint64_t c2) {
        r1_ = r1 - 1;
        c1_ = c1 - 1;
        r2_ = r2;
        c2_ = c2;
    }

    Matrix_coords(uint64_t r1, uint64_t c1) {
        r1_ = r1 - 1;
        c1_ = c1 - 1;
        r2_ = r1_;
        c2_ = c1_;
    }
};

class Matrix_row_coords {
public:
    uint64_t r1_, c1_, c2_;

    Matrix_row_coords(uint64_t r1, uint64_t c1, uint64_t c2, uint64_t width) {
        r1_ = r1 - 1;
        c1_ = c1 - 1;
        c2_ = c2;
    }

    Matrix_row_coords(uint64_t r1, uint64_t c1) {
        r1_ = r1 - 1;
        c1_ = c1 - 1;
        c2_ = c1_;
    }
};

class Matrix_column_coords {
public:
    uint64_t r1_, c1_, r2_;

    Matrix_column_coords(uint64_t r1, uint64_t c1, uint64_t r2, uint64_t hight) {
        r1_ = r1 - 1;
        c1_ = c1 - 1;
        r2_ = r2;

    }

    Matrix_column_coords(uint64_t r1, uint64_t c1) {
        r1_ = r1 - 1;
        c1_ = c1 - 1;
        r2_ = r1_;
    }
};

template <typename T>
class Matrix;

template <typename Tval>
class MatrixProxy {
private:
    std::unordered_map<std::pair<uint64_t, uint64_t>, Tval, pair_hash>* pmatrix;
    inline static double eps = 0.0000000001;
    bool is_vector;
    uint64_t r1, c1, r2, c2;
public:
    std::unordered_map<std::pair<uint64_t, uint64_t>, Tval, pair_hash>* get_pmatrix() {
        return pmatrix;
    }

    void set_null() {
        pmatrix = nullptr;
    }
    
    uint64_t get_r1() {
        return r1;
    }
    
    uint64_t get_c1() {
        return c1;
    }

    uint64_t get_r2() {
        return r2;
    }

    uint64_t get_c2() {
        return c2;
    }

    MatrixProxy() {
        pmatrix = nullptr;
        r1 = r2 = c1 = c2 = 0;
    }

    MatrixProxy(Matrix<Tval>* matrix, Matrix_coords coord) {
        pmatrix = matrix->get_matrix_pointer();
        this->r1 = coord.r1_;
        this->c1 = coord.c1_;
        this->r2 = coord.r2_;
        this->c2 = coord.c2_;
        is_vector = false;
    }

    MatrixProxy(Matrix<Tval>* matrix, Matrix_row_coords coord) {
        pmatrix = matrix->get_matrix_pointer();
        this->r1 = coord.r1_;
        this->c1 = coord.c1_;
        this->r2 = coord.r1_;
        this->c2 = coord.c2_;
        is_vector = true;
    }

    MatrixProxy(Matrix<Tval>* matrix, Matrix_column_coords coord) {
        pmatrix = matrix->get_matrix_pointer();
        this->r1 = coord.r1_;
        this->c1 = coord.c1_;
        this->r2 = coord.r2_;
        this->c2 = coord.c1_;
        is_vector = true;
    }

    Tval operator () (uint64_t i, uint64_t j) {
        try {
            if (i == 0 || i > r2 - r1)
                throw OutOfRange("Out of range. Column coordinate is ", std::to_string(i));
            else if (j == 0 || j > c2 - c1)
                throw OutOfRange("Out of range. Row coordinate is ", std::to_string(j));
            else
                return (*pmatrix).at({i - r1 - 1, j - c1 - 1});
        } catch(std::out_of_range e) {
            return Tval(0);
        }
        return Tval(0);   
    }
};



template <typename T>
/**
 * Class of Sparse Matrices.
 */
class Matrix {
private:
    /**
     * Map for numbers in matrix.
     */    
    std::unordered_map<std::pair<uint64_t, uint64_t>, T, pair_hash> matrix_;
    
    /**
     * Epsilon: -eps < number < eps means number == 0.
     */
    inline static double eps = 0.0000000001;
    
    /**
     * Number of lines.
     */
    uint64_t hight;
    
    /**
     * Number of columns.
     */
    uint64_t width;


    std::set<MatrixProxy<T>*> proxies;

public:

    
    /**
     * Default constructor, initialises hight and widht with 0.
     */
    Matrix() {
        hight = 0;
        width = 0;
    }

    // ~Matrix() {
    //     for (auto proxy : proxies) {
    //         proxy->set_null();
    //     }
    // }

    /**
     * Constructor from size. Creates identity matrix.
     * 
     * @param  hight : number of lines.
     * @param  width : number of columns.
     */
    Matrix(uint64_t hight, uint64_t width) {
        this->hight = hight;
        this->width = width;
        for (size_t i=0; i < hight; ++i) {
            matrix_[{i, i}] = T(1);
        }
    }

    /**
     * Create matrix with values as numbers.
     * 
     * @param  value : value to initialize each cell.
     * @param  hight : number of lines.
     * @param  width : number of columns.
     */
    Matrix(const int64_t value, const uint64_t hight, const uint64_t width) {
        if (bool(value)) {
            for (size_t i = 0; i < hight; ++i) {
                for (size_t j = 0; j < width; j++) {
                    matrix_[{i, j}] = T(value);
                }
            }
        }
        this->hight = hight;
        this->width = width;
    }

    /**
     * Copy constructor
     * 
     * @param  right : matrix to construct from.
     */
    Matrix(const Matrix& right) {
        matrix_ = right.matrix_;
        hight = right.hight;
        width = right.width;
    }


    bool operator ==(const Matrix& right) {
        for (size_t i=1; i <= hight; i++) {
            for (size_t j=1; j <= width; j++) {
                if (matrix_(i, j) != right.matrix_(i, j))
                    return false;
            }
        }
        return true;
    }
    /**
     * Constructor from unordered map. 
     * 
     * @param  matrix    : matrix in unordered map representation.
     * @param  hight     : number of lines.
     * @param  width     : number of columns.
     */
    Matrix(const std::unordered_map<std::pair<uint64_t, uint64_t>, T, pair_hash>& matrix, uint64_t hight, uint64_t width) {
        this->matrix_ = matrix;
        this->hight = hight;
        this->width = width;
    }

    Matrix(MatrixProxy<T> mp) {
        for (auto elem : *(mp.get_pmatrix())) {
            if (mp.get_r1() <= elem.first.first < mp.get_r2() && mp.get_c1() <= elem.first.second < mp.get_c2()) {
                matrix_[{elem.first.first - mp.get_r1(), elem.first.second - mp.get_c1()}] = elem.second;
            }
        }
        hight = mp.get_r2() - mp.get_r1();
        width = mp.get_c2() - mp.get_c1();
    }

    const uint64_t get_hight() const {
        return hight;
    }

    const uint64_t get_width() const {
        return width;
    }

    /**
     * Operator [].
     * 
     * @param  p    : coordinates.
     * @return {T}  : reference to element.
     */
    T& operator [] (const std::pair<uint64_t, uint64_t> p) {
        if (p.first <= 0 || hight < p.first)
            throw OutOfRange("Matrix hight out of range");
        if (p.second <= 0 || width < p.second)
            throw OutOfRange("Matrix width out of range");
        return matrix_[{p.first-1, p.second-1}];
    } 


    /**
     * Constructor from filename. Template must be previously defined with Parser.analyze_file(std::string fname).
     * 
     * @param  fname : filename to construct from.
     */
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
                        if (hight <= coord.second) {
                            throw OutOfRange("Matrix hight coordinate out of range");
                        }
                        iss >> word;
                        coord.second = std::stoi(word) - 1;
                        if (width <= coord.second) {
                            throw OutOfRange("Matrix width coordinate out of range");
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
                                matrix_[coord] = T(first, second);
                            } else {
                                matrix_[coord] = T(second);
                            }
                            break;
                        case 'c':
                            if (first == "") {
                                first = second;
                                second = "0";
                            }
                            if (first.find('.') != -1) {
                                if (second.find('.') != -1)
                                    matrix_[coord] = T(std::stod(first), std::stod(second));
                                else
                                    matrix_[coord] = T(std::stod(first), std::stoi(second));
                            } else {
                                if (second.find('.') != -1) {
                                    matrix_[coord] = T(std::stoi(first), std::stod(second));
                                }
                                else {
                                    matrix_[coord] = T(std::stoi(first), std::stoi(second));
                                }
                            }
                            break;
                        }
                        break;
                    }
                } while (iss);
            }
            input.close();
        } else {
            throw FileNotFound("Matrix constructor: not found", fname);
        }
    }
    
    /**
     * Add other matrix.
     * 
     * @param  right     : other matrix.
     * @return {Matrix}  : value of sum.
     */
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

    std::unordered_map<std::pair<uint64_t, uint64_t>, T, pair_hash>* get_matrix_pointer() {
        return &matrix_;
    }

    /**
     * Substract other matrix.
     * 
     * @param  right     : other matrix.
     * @return {Matrix}  : sub of matrices.
     */
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



    /**
     * Multiply matrices.
     * 
     * @param  right      : other matrix.
     * @return {Matrix}   : product of matrices.
     */
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
        for (auto kv : right.matrix_) {
            non_zero_columns.insert(kv.first.second);
        }
        
        for (auto i : non_zero_lines) {
            for (auto j : non_zero_columns) {
                res.matrix_[{i, j}] = T(0);
                for (size_t k=0; k < width; ++k) {
                    res.matrix_[{i, j}] += (*this)(i+1, k+1) * right(k+1, j+1); // operator () works with i+1
                }
                if (res(i+1, j+1).is_zero(eps))
                    res.matrix_.erase({i, j});
            }
        }
        
        return res;
    }

    
    /**
     * Unary minus.
     * 
     * @return {Matrix}  : this matrix with changed sign.
     */
    Matrix operator-() const {
        Matrix res(*this);
        for (auto kv : matrix_) {
            res.matrix_[kv.first] = -kv.second;
        }
        return res;
    }

    
    /**
     * Copy operator.
     * 
     * @param  right            : matrix to copy.
     * @return {const Matrix&}  : this matrix.
     */
    const Matrix& operator=(const Matrix& right) {
        hight = right.hight;
        width = right.width;

        matrix_ = right.matrix_;
    }
    
    
    /**
     * Convert to string.
     * 
     * @return {std::string}  : matrix value converted to string.
     */
    std::string to_string() const {
        std::string res = "";
        for (size_t i=0; i < hight; ++i) {
            for (size_t j=0; j < width; ++j) {
                res += (*this)(i+1, j+1).to_string() + " ";
            }
            res += "\n";

        }
        return res;
    }

    
    /**
     * Print to std::ostream.
     * 
     * @param  str             : stream to print matrix.
     * @param  matrix          : matrix to print.
     * @return {std::ostream}  : stream with printed matrix.
     */
    friend std::ostream & operator<<(std::ostream & str, const Matrix & matrix) {
        str << matrix.to_string();
        return str;
    }

    
    /**
     * Get element to read.
     * 
     * @param  i    : line coordinate.
     * @param  j    : column coordinate.
     * @return {T}  : element.
     */
    T operator () (const uint64_t i, const uint64_t j) const {
        try {
            if (i <= 0 || hight < i)
                throw OutOfRange("Matrix hight out of range");
            if (j <= 0 || width < j)
                throw OutOfRange("Matrix width out of range");
            return matrix_.at({i-1, j-1});
        } catch (std::out_of_range) {
            return T(0);
        } 
        return T(0);
    }

    MatrixProxy<T> operator[] (Matrix_coords coord) {
        std::cout << "aslhfdgakhf" << std::endl;
        if (coord.c2_ == -1) {
            coord.c2_ = width;
        }
        if (coord.r2_ == -1) {
            coord.r2_ = hight;
        }
        MatrixProxy mp(this, coord);
        proxies.insert(&mp);
        return mp;
    }
};



#endif
