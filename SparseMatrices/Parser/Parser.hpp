// #include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Parser {
public:
    const int analyze_file(std::string fname);

    // template <typename T>
    // const Matrix<T>& parse_as_matrix();
    
    // template <typename T>
    // int parse_as_vector(std::string fname, Vector<T>& res) {
    // }
   

    auto parse();

};
