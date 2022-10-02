#include <cmath>
#include <climits>
#include <numeric>

class RationalNumber {
private:
    long long numerator;
    unsigned long long denominator;

public:
    RationalNumber();
    RationalNumber(const RationalNumber& right);
    RationalNumber(const long long& numerator, const unsigned long long& denominator);

    template<typename T>
    RationalNumber(T num);

    const RationalNumber operator+(const RationalNumber& right) const;
    const RationalNumber operator-(const RationalNumber& right) const;
    const RationalNumber operator*(const RationalNumber& right) const;
    const RationalNumber operator/(const RationalNumber& right) const;

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
};
