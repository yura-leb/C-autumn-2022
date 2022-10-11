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

RationalNumber::RationalNumber(const LongNumber& numerator, const LongNumber& denominator=LongNumber(1)) {
    this->numerator = numerator;
    this->denominator = denominator;
    make_canonical();
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
    make_canonical();
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

RationalNumber& RationalNumber::operator++() {
    *this += 1;
    make_canonical();
    return *this;
}

RationalNumber& RationalNumber::operator--() {
    *this -= 1;
    make_canonical();
    return *this;
}

RationalNumber RationalNumber::operator++(int) {
    RationalNumber tmp(*this);
    std::cout << *this << tmp << std::endl;
    operator++();
    std::cout << *this << tmp << std::endl;
    return tmp;
}
RationalNumber RationalNumber::operator--(int) {
    RationalNumber tmp(*this);
    operator--();
    return tmp;
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
    numerator.remove_leading_zeros();
    // denominator.remove_leading_zeros();
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


RationalNumber::operator int () const {
    return int(numerator / denominator);
} 

RationalNumber::operator long () const {
    return long(numerator / denominator);
} 

RationalNumber::operator short () const {
    return short(numerator / denominator);
} 

RationalNumber round(const RationalNumber& number) {
    RationalNumber tmp = number.numerator < 0 ? RationalNumber(-1, 2) + number : RationalNumber(1, 2) + number;

    return RationalNumber(tmp.numerator / tmp.denominator);
}

RationalNumber floor(const RationalNumber& number) {

    LongNumber divisor = number.numerator / number.denominator;
    LongNumber remainder = number.numerator % number.denominator;

    if (number.numerator._is_negative() && remainder)
        return RationalNumber(divisor - 1);
    else
        return RationalNumber(divisor);

}



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
