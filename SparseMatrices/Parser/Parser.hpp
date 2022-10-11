#ifndef PARSER_HPP
#define PARSER_HPP

// #include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Class parser for parsing files. Creates Vector and Matrix with complex or rational elements.
 */
class Parser {
public:
    
    /**
     * Get type of object in file.
     * 
     * @param  fname  : filename with data.
     * @return {int}  : returns 2-digit number. First number 1: vector, 2:matrix. Second number: 2:rational, 3: complex.
     */
    const int analyze_file(std::string fname);

    // template <typename T>
    // const Matrix<T>& parse_as_matrix();
    
    // template <typename T>
    // int parse_as_vector(std::string fname, Vector<T>& res) {
    // }
   

    auto parse();

};

#endif
