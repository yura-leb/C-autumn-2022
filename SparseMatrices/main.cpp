#include <iostream>
#include "OutOfRange.hpp"
#include "ComplexNumber.hpp"
#include "RationalNumber.hpp"
#include "Matrix.hpp"
#include "Parser.hpp"
#include "ZeroDivision.hpp"
#include "Vector.hpp"
#include <string>

int main() {
    // LongNumber x(10);
    // LongNumber y(-10);
    // std::cout << x + y << std::endl;
    std::cout << "hello" << std::endl;
    LongNumber b(-5);
    std::cout << b << std::endl;
    std::cout << (b * 44) << std::endl;

    RationalNumber a("-5/3");
    std::cout << a << std::endl;
    std::cout << a * 10 << std::endl;


    Parser p;
    int res = p.analyze_file("example.txt");
    std::cout << res << std::endl;
    if (res == 12) {
        std::cout << "file analyzed" << std::endl;
        try {
            Vector<RationalNumber> v("example.txt");
        // p.parse_as_vector("SparseMatrices/example.txt", v);
        
        std::cout << v(9) << std::endl;
        std::cout << "first" << std::endl;
        try {
            std::cout << v / 0 << std::endl;
        } catch(ZeroDivision e) {
            std::cout << e << std::endl;
        }
        std::cout << "second" << std::endl;
        std::cout << 10 * v << std::endl;
        std::cout << v + v << std::endl;
        } catch (WrongInput e) {
            std::cout << e << std::endl;
        }

        // try {
        //     ComplexNumber y(1000000000000000000000000000000000000, 3);
        
        //     std::cout << short(y) << std::endl;
        // }
        // catch (BadCast e) {
        //     std::cout << e << std::endl;

        // }
    }

    res = p.analyze_file("matrix_example.txt");
    std::cout << res << std::endl;
    if (res == 22) {
        std::string y = "matrix_example.txt";
        try {
            Matrix<RationalNumber> m("matrix_example.txt");
            Matrix<RationalNumber> n(1, 5, 5);
            std::cout << m << std::endl;
            std::cout << n << std::endl;
            std::cout << m + n << std::endl;
            std::cout << m - n << std::endl;
            std::cout << m * n << std::endl;

        } catch (std::invalid_argument) {
            std::cout << "invalid argument" << std::endl;
        }
    }

    // ComplexNumber<> c(1.0, 2.0);
    // std::cout << c << std::endl;
    // RationalNumber b(4);

    // LongNumber a(0);
    // std::cout << a << std::endl;
    // std::string str("-902");
    // LongNumber b(str);
    // std::cout << "b " << b + 0 << std::endl;
    // LongNumber c("-200");
    // std::cout << c << std::endl;
    // std::cout << (a < b) << (c < b) << (c < a) << std::endl;

    // c = a + b;
    // // c = -100;
    // std::cout << "c " << c << std::endl;
    // std::cout << " c * " << c * 10 << std::endl;
    // std::cout << "c / " << c / 102 << std::endl;
    // std::cout << "c / " << c / 10 << std::endl;
    // std::cout << "c / " << c / 2 << std::endl;
    // std::cout << "c / " << c / 15 << std::endl;
    // std::cout << "c / " << c / 1500 << std::endl;

    // std::cout << std::endl << "strings" << std::endl;
    // std::string s("qwerty");
    // std::cout << (s == "qwerty") << std::endl;
}