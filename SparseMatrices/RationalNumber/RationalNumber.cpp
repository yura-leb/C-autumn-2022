#include <iostream>
#include "RationalNumber.hpp"
#include "ZeroDivision.hpp"

// constructor
RationalNumber::RationalNumber() {
    numerator = LongNumber(0);
    denominator = LongNumber(1);
}

RationalNumber::RationalNumber(const RationalNumber& right) {
    numerator = right.numerator;
    denominator = right.denominator;
}

RationalNumber::RationalNumber(const LongNumber& numerator, const LongNumber& denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

RationalNumber::RationalNumber(std::string right) {
    int pos;
    if ((pos = right.find('/')) != -1) {
        numerator = LongNumber(right.substr(0, pos));
        denominator = LongNumber(right.substr(pos + 1));
    } else {
        numerator = LongNumber(right);
        denominator = LongNumber(1);
    }
}

RationalNumber::RationalNumber(int64_t num) {
    numerator = LongNumber(num);
    denominator = LongNumber(1);
}

// arithmetic

RationalNumber RationalNumber::operator+(const RationalNumber& right) const {
    LongNumber result_numerator = numerator * right.denominator + right.numerator * denominator;
    LongNumber result_denominator = denominator * right.denominator;
    return RationalNumber(result_numerator, result_denominator).make_canonical();
}

RationalNumber RationalNumber::operator-(const RationalNumber& right) const {
    LongNumber result_numerator = numerator * (right.denominator) -
                                     right.numerator * (denominator);
    LongNumber result_denominator = denominator * right.denominator;
    return RationalNumber(result_numerator, result_denominator).make_canonical();
}

RationalNumber RationalNumber::operator*(const RationalNumber& right) const {
    // std::cout << numerator << " " << right.numerator << " " << denominator << " " << right.denominator << std::endl;;
    return RationalNumber(numerator * right.numerator, denominator * right.denominator).make_canonical();
}

RationalNumber RationalNumber::operator/(const RationalNumber& right) const {
    if (right.numerator != 0 && denominator != 0) {
        return RationalNumber(
                              numerator * right.denominator * (right.numerator._is_negative() ? -1 : 1), 
                              denominator * abs(right.numerator)
                             ).make_canonical();
    } else {
        throw ZeroDivision("Rational Number zero division error: ", (*this).to_string(), right.to_string());
    }
}


RationalNumber RationalNumber::operator-() const {
    return RationalNumber(-numerator, denominator);
}


// compare

bool operator<(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * (right.denominator) < right.numerator * (left.denominator);
}

bool operator<=(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * (right.denominator) <= right.numerator * (left.denominator);
}

bool operator>(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * (right.denominator) > right.numerator * (left.denominator);
}

bool operator>=(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * (right.denominator) >= right.numerator * (left.denominator);
}

bool operator==(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * (right.denominator) == right.numerator * (left.denominator);
}

bool operator!=(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * (right.denominator) != right.numerator * (left.denominator);
}


// assignment

RationalNumber& RationalNumber::operator=(const RationalNumber& right) {
    if (this == &right) {
        return *this;
    }

    numerator = right.numerator;
    denominator = right.denominator;
    return *this;
}

RationalNumber& operator+=(RationalNumber& left, const RationalNumber& right) {
    left = left + right;
    return left;
}

RationalNumber& operator-=(RationalNumber& left, const RationalNumber& right) {
    left = left - right;
    return left;
}

RationalNumber& operator*=(RationalNumber& left, const RationalNumber& right) {
    left = left * right;
    return left;
}

RationalNumber& operator/=(RationalNumber& left, const RationalNumber& right) {
    left = left / right;
    return left;
}

const RationalNumber& operator++(RationalNumber& rat_num) {
    rat_num.numerator += rat_num.denominator;
    return rat_num;
}

const RationalNumber& operator--(RationalNumber& rat_num) {
    rat_num.numerator -= rat_num.denominator;
    return rat_num;
}

const LongNumber least_common_quotient(const LongNumber& a, const LongNumber& b) {
    return a * b / gcd(a, b); 
}

RationalNumber RationalNumber::make_canonical() {
    LongNumber greatest_common_divider(gcd(abs(numerator), abs(denominator)));
    if (greatest_common_divider != 1) {
        numerator /= greatest_common_divider;
        denominator /= greatest_common_divider;
    }
    return *this;
}

std::string RationalNumber::to_string() const {
    return numerator.to_string() + "/" + denominator.to_string();
}

std::ostream & operator<<(std::ostream & str, const RationalNumber & number) {
  str << number.to_string();
  return str;
}

bool RationalNumber::is_zero(double eps) const {
    int denom = 1;
    while (abs(eps) < 1) {
        denom *= 10;
        eps *= 10;
    }
    RationalNumber epsilon(int(eps), denom);
    return (-epsilon < *this && *this < epsilon);
}


// RationalNumber::operator int () const {
//     // std::cout << (INT_MIN) << " " << (numerator / denominator) << " " << numerator << " " << INT_MAX * denominator << std::endl;
//     if ((INT_MIN * denominator < numerator) && (numerator < INT_MAX * denominator)) {
//         return numerator / (denominator);
//     } else {
//         // exception
//         std::cout << "Int error" << std::endl;
//         return 0;
//     }
// } 

// RationalNumber::operator long () const {
//     if (((LONG_MIN * denominator) < numerator) && (numerator < (LONG_MAX * denominator))) {
//         return numerator / denominator);
//     } else {
//         // exception
//         std::cout << "Long error" << std::endl;
//         return 0;
//     }
// } 

// RationalNumber::operator short () const {
//     if (((denominator * SHRT_MIN) < numerator) && (numerator < (SHRT_MAX * denominator))) {
//         return numerator / denominator;
//     } else {
//         // exception
//         std::cout << "Short error" << std::endl;
//         return 0;
//     }
// } 

// RationalNumber RationalNumber::round() {
//     RationalNumber tmp = numerator < 0 ? RationalNumber(-1, 2) + *this : RationalNumber(1, 2) + *this;

//     return RationalNumber(tmp.numerator / (tmp.denominator));
// }

// RationalNumber RationalNumber::floor() {

//     LongNumber divisor = numerator / denominator;
//     LongNumber remainder = numerator % denominator;

//     if (numerator._is_negative() && remainder)
//         return RationalNumber(divisor - 1);
//     else
//         return RationalNumber(divisor);

// }



// int main() {
//     LongNumber a(1);
//     // std::cout << a << std::endl;
//     // RationalNumber c(-5, 2), d(-3, 2), a(3, 2), b(5, 2);
//     // std::cout << -5/3 << " " << -5%3 << std::endl;
//     // std::cout <<int(c) << " " << int(d) << " " << int(a) << " " << int(b) << std::endl;
//     // c.floor().print();
//     // d.floor().print();
//     // a.floor().print();
//     // b.floor().print();
//     return 0;
// }
