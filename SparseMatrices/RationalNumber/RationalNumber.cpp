#include <iostream>

#include "RationalNumber.h"



// constructor
RationalNumber::RationalNumber() {
    this->numerator = 1;
    this->denominator = 1;
}

RationalNumber::RationalNumber(const RationalNumber& right) {
    numerator = right.numerator;
    denominator = right.denominator;
}

RationalNumber::RationalNumber(const long long& numerator, const unsigned long long& denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

void RationalNumber::print() {
    std::cout << numerator << " " << denominator << std::endl;
}

template<typename T>
RationalNumber::RationalNumber(T num) {
    numerator = num;
    denominator = 1;
}



// arithmetic

const RationalNumber RationalNumber::operator+(const RationalNumber& right) const {
    long long result_numerator = numerator * static_cast<long long>(right.denominator) +
                                     right.numerator * static_cast<long long>(denominator);
    unsigned long long result_denominator = denominator * right.denominator;
    return RationalNumber(result_numerator, result_denominator).make_canonical();
}

const RationalNumber RationalNumber::operator-(const RationalNumber& right) const {
    long long result_numerator = numerator * static_cast<long long>(right.denominator) -
                                     right.numerator * static_cast<long long>(denominator);
    unsigned long long result_denominator = denominator * right.denominator;
    return RationalNumber(result_numerator, result_denominator).make_canonical();
}

const RationalNumber RationalNumber::operator*(const RationalNumber& right) const {
    return RationalNumber(numerator * static_cast<long long>(right.numerator), denominator * right.denominator).make_canonical();
}

const RationalNumber RationalNumber::operator/(const RationalNumber& right) const {
    if (right.numerator) {
        return RationalNumber(numerator * static_cast<long long>(right.denominator) * right.numerator * abs(right.numerator), 
                          denominator * abs(right.numerator)).make_canonical();
    } else {
        // exception
        return RationalNumber();
    }
}



// compare

bool operator<(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * static_cast<long long>(right.denominator) < right.numerator * static_cast<long long>(left.denominator);
}

bool operator<=(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * static_cast<long long>(right.denominator) <= right.numerator * static_cast<long long>(left.denominator);
}

bool operator>(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * static_cast<long long>(right.denominator) > right.numerator * static_cast<long long>(left.denominator);
}

bool operator>=(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * static_cast<long long>(right.denominator) >= right.numerator * static_cast<long long>(left.denominator);
}

bool operator==(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * static_cast<long long>(right.denominator) == right.numerator * static_cast<long long>(left.denominator);
}

bool operator!=(const RationalNumber& left, const RationalNumber& right) {
    return left.numerator * static_cast<long long>(right.denominator) != right.numerator * static_cast<long long>(left.denominator);
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

const unsigned long long least_common_quotient(const unsigned long long& a, const unsigned long long& b) {
    return a * b / std::gcd(a, b); 
}

RationalNumber RationalNumber::make_canonical() {
    long long greatest_common_divider = std::gcd(numerator, denominator);
    numerator /= greatest_common_divider;
    denominator /= greatest_common_divider;
    return *this;
}

RationalNumber::operator int () const {
    // std::cout << static_cast<long long>(INT_MIN) << " " << static_cast<long long>(numerator / denominator) << " " << numerator << " " << INT_MAX * denominator << std::endl;
    if ((INT_MIN * static_cast<long long>(denominator) < numerator) && (numerator < INT_MAX * static_cast<long long>(denominator))) {
        return numerator / static_cast<long long>(denominator);
    } else {
        // exception
        std::cout << "Int error" << std::endl;
        return 0;
    }
} 

RationalNumber::operator long () const {
    if ((static_cast<long long>(LONG_MIN * denominator) < numerator) && (numerator < static_cast<long long>(LONG_MAX * denominator))) {
        return static_cast<long>(numerator / denominator);
    } else {
        // exception
        std::cout << "Long error" << std::endl;
        return 0;
    }
} 

RationalNumber::operator short () const {
    if ((static_cast<long long>(SHRT_MIN * denominator) < numerator) && (numerator < static_cast<long long>(SHRT_MAX * denominator))) {
        return static_cast<short>(numerator / denominator);
    } else {
        // exception
        std::cout << "Short error" << std::endl;
        return 0;
    }
} 

RationalNumber RationalNumber::round() {
    RationalNumber tmp = numerator < 0 ? RationalNumber(-1, 2) + *this : RationalNumber(1, 2) + *this;

    return RationalNumber(tmp.numerator / static_cast<long long>(tmp.denominator));
}

RationalNumber RationalNumber::floor() {
    int sign = numerator < 0 ? -1 : 1;

    long long divisor = numerator / static_cast<long long>(denominator);
    long long remainder = numerator % static_cast<long long>(denominator);

    if (sign < 0 && remainder)
        return RationalNumber(divisor - 1);
    else
        return RationalNumber(divisor);

}



int main() {
    RationalNumber c(-5, 2), d(-3, 2), a(3, 2), b(5, 2);
    std::cout << -5/3 << " " << -5%3 << std::endl;
    std::cout <<int(c) << " " << int(d) << " " << int(a) << " " << int(b) << std::endl;
    c.floor().print();
    d.floor().print();
    a.floor().print();
    b.floor().print();
    return 0;
}
