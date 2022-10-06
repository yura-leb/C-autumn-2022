#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <cmath>
#include <climits>
#include <numeric>
#include "LongNumber.hpp"


class RationalNumber {
private:
    LongNumber numerator;
    LongNumber denominator;

public:
    RationalNumber();
    RationalNumber(const RationalNumber& right);
    RationalNumber(const LongNumber& numerator, const LongNumber& denominator);
    RationalNumber(std::string right);
    RationalNumber(int64_t num);

    RationalNumber operator+(const RationalNumber& right) const;
    RationalNumber operator-(const RationalNumber& right) const;
    RationalNumber operator*(const RationalNumber& right) const;
    RationalNumber operator/(const RationalNumber& right) const;

    RationalNumber operator-() const;

    friend bool operator<(const RationalNumber& left, const RationalNumber& right);
    friend bool operator<=(const RationalNumber& left, const RationalNumber& right);
    friend bool operator>(const RationalNumber& left, const RationalNumber& right);
    friend bool operator>=(const RationalNumber& left, const RationalNumber& right);
    friend bool operator==(const RationalNumber& left, const RationalNumber& right);
    friend bool operator!=(const RationalNumber& left, const RationalNumber& right);
    friend bool operator==(const RationalNumber& left, const RationalNumber& right);

    RationalNumber& operator=(const RationalNumber& right);
    friend RationalNumber& operator+=(RationalNumber& left, const RationalNumber& right);
    friend RationalNumber& operator-=(RationalNumber& left, const RationalNumber& right);

    friend const RationalNumber& operator++(RationalNumber& rat_num);
    friend const RationalNumber& operator--(RationalNumber& rat_num);

    explicit operator int () const;
    explicit operator long () const;
    explicit operator short () const;

    RationalNumber round();
    RationalNumber floor();

    RationalNumber make_canonical();


    void print();
    std::string to_string() const;
    bool is_zero(double eps) const;
    friend std::ostream & operator<<(std::ostream & str, RationalNumber const & number);

};

#endif
