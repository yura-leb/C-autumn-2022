#include "Parser.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;


const int Parser::analyze_file(std::string fname) {
    std::string line, word;
    int res = 0;
    bool comment;
    
    std::fstream my_file (fname);
    std::string path = ".";
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
    my_file.close();
	return 0;

    // std::ifstream input (fname);
    // if (input.is_open())
    // {
    //     while ( getline (input,line) )
    //     {
    //         std::istringstream iss(line);
    //         do {
    //             iss >> word;
    //             if (word[0] == '#') {
    //                 comment = true;
    //                 break;
    //             } else if (word == "vector") {
    //                 res = 10;
    //             }
    //             else if (word == "matrix") {
    //                 res = 20;
    //             }
    //             else if (word == "bool") {
    //                 res += 1;
    //             }
    //             else if (word == "rational") {
    //                 res += 2;
    //             }
    //             else if (word == "complex") {
    //                 res += 3;
    //             }
    //             else {
    //                 break;
    //             }
    //         } while (iss);

    //         if (comment) {
    //             comment = false;
    //             continue;
    //         } else {
    //             break;
    //         }
    //     }
    //     input.close();
    // }
    // return res;

 
	// my_file.close();
	// return 0;
    // std::string path = "";
    // for (const auto & entry : fs::directory_iterator(path))
    //     std::cout << entry.path() << std::endl;
    // return 0;
}

// template <typename T>
// const Vector<T>& Parser::parse_as_vector(std::string fname) {
    // std::string line, word, first = "", second = "";
    // uint64_t coord;
    // bool is_complex = false;
    // Vector<T> res;
    // std::ifstream input (fname);
    // if (input.is_open())
    // {
    //     while ( getline (input,line) )
    //     {
    //         first = "";
    //         second = "";
    //         std::istringstream iss(line);

    //         do {
    //             iss >> word;
    //             if (word == "vector") {
    //                 iss >> word;
    //                 if (word == "complex") {
    //                     is_complex = true;
    //                 }
    //                 iss >> word;
    //                 res.set_len(std::stoi(word));
    //                 break;
    //             } else if (word[0] == '#') {
    //                 break;
    //             } else {
    //                 coord = std::stoi(word);
    //                 iss >> word;
    //                 for (auto letter : word) {
    //                     if ('0' <= letter && letter <= '9' || letter == '.') {
    //                         second += letter;
    //                     } else if (letter == '/') {
    //                         first = second;
    //                         second = "";
    //                     } else if (letter == '\n' || letter == '#') {
    //                         break;
    //                     }
    //                 }
    //                 if (first != "") {
    //                     res(coord) = T(first, second);
    //                 } else {
    //                     // добавить int long short ...
    //                     res(coord) = T(second);
    //                 }
    //                 break;

    //             }
    //         } while (iss);
    //     }
    //     input.close();
    // }
    // std::cout << res << std::endl;
    // return res;
// }
