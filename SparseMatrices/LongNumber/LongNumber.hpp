#ifndef LONG_NUMBER_HPP
#define LONG_NUMBER_HPP

#include <string>
#include <algorithm>

class LongNumber {
public:
    LongNumber();
    LongNumber(const LongNumber& right);
    LongNumber(const std::string str);
    LongNumber(const char* right) : LongNumber(std::string(right)) {}

    template<typename T>
    LongNumber(const T& right) : LongNumber(std::to_string(right)) {}


    LongNumber operator+() const;
    LongNumber operator-() const;
    friend LongNumber operator+(const LongNumber& left, const LongNumber& right);
    friend LongNumber operator-(const LongNumber& left, const LongNumber& right);
    friend LongNumber operator*(const LongNumber& left, const LongNumber& right);
    friend LongNumber operator/(const LongNumber& left, const LongNumber& right);
    friend LongNumber operator%(const LongNumber& left, const LongNumber& right);


    friend bool operator<(const LongNumber& left, const LongNumber& right);
    friend bool operator<=(const LongNumber& left, const LongNumber& right);
    friend bool operator>(const LongNumber& left, const LongNumber& right);
    friend bool operator>=(const LongNumber& left, const LongNumber& right);
    friend bool operator==(const LongNumber& left, const LongNumber& right);
    friend bool operator!=(const LongNumber& left, const LongNumber& right);

    LongNumber& operator=(const LongNumber& right);

    friend LongNumber& operator+=(LongNumber& left, const LongNumber& right);
    friend LongNumber& operator-=(LongNumber& left, const LongNumber& right);
    friend LongNumber& operator*=(LongNumber& left, const LongNumber& right);
    friend LongNumber& operator/=(LongNumber& left, const LongNumber& right);

    friend LongNumber gcd(const LongNumber& a, const LongNumber& b);
    LongNumber& operator++();
    LongNumber& operator--();
    LongNumber operator++(int);
    LongNumber operator--(int);

    friend std::ostream & operator<<(std::ostream & str, LongNumber const & long_number);
    explicit operator bool () const;

    std::string to_string() const;
    std::string get_number() const;
    bool _is_negative() const;
    void remove_leading_zeros();
    LongNumber make_canonical();

    friend const LongNumber abs(const LongNumber& long_number);

private:
    std::string number;
    bool is_negative;
    const int step = 6;


    const double eps = 0.0000001;
    const int digits_after_comma = 7;
};

#endif