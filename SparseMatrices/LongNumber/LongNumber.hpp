#include <string>
#include <algorithm>

class LongNumber {
public:
    LongNumber();
    LongNumber(const LongNumber& right);
    LongNumber(const std::string str);
    // LongNumber(const char* str);

    LongNumber(const long long right);


    const LongNumber operator+() const;
    const LongNumber operator-() const;
    friend const LongNumber operator+(const LongNumber& left, const LongNumber& right);
    friend const LongNumber operator-(const LongNumber& left, const LongNumber& right);
    friend const LongNumber operator*(const LongNumber& left, const LongNumber& right);
    friend const LongNumber operator/(const LongNumber& left, const LongNumber& right);
    friend const LongNumber operator%(const LongNumber& left, const LongNumber& right);


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

    friend const LongNumber& gcd(const LongNumber& a, const LongNumber& b);
    friend const LongNumber& operator++(LongNumber& rat_num);
    friend const LongNumber& operator--(LongNumber& rat_num);

    friend std::ostream & operator<<(std::ostream & str, LongNumber const & long_number);
    operator bool () const;

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
