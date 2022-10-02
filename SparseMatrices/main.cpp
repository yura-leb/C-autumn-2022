#include <iostream>

#include "ComplexNumber.hpp"
#include "RationalNumber.hpp"
// #include "Vector.hpp"

int main() {
    // LongNumber x(10);
    // LongNumber y(-10);
    // std::cout << x + y << std::endl;
    std::cout << "hello" << std::endl;

    RationalNumber a(1);
    a.print();

    LongNumber b(2);
    std::cout << b << std::endl;

    ComplexNumber<int, int> c(1, 2);
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