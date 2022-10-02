#include <string>
#include <algorithm>

class LongNumber {
public:
    LongNumber();
    LongNumber(const LongNumber& right);
    LongNumber(const std::string str);
    LongNumber(const char* str);

    template<typename T>
    LongNumber(const T right);


    const LongNumber operator+() const;
    const LongNumber operator-() const;
    const LongNumber operator+(const LongNumber& right) const;
    const LongNumber operator-(const LongNumber& right) const;
    const LongNumber operator*(const LongNumber& right) const;
    const LongNumber operator/(const LongNumber& right) const;

    friend bool operator<(const LongNumber& left, const LongNumber& right);
    friend bool operator<=(const LongNumber& left, const LongNumber& right);
    friend bool operator>(const LongNumber& left, const LongNumber& right);
    friend bool operator>=(const LongNumber& left, const LongNumber& right);
    friend bool operator==(const LongNumber& left, const LongNumber& right);
    friend bool operator!=(const LongNumber& left, const LongNumber& right);

    LongNumber& operator=(const LongNumber& right);
    friend LongNumber& operator+=(LongNumber& left, const LongNumber& right);
    friend LongNumber& operator-=(LongNumber& left, const LongNumber& right);

    friend const LongNumber& operator++(LongNumber& rat_num);
    friend const LongNumber& operator--(LongNumber& rat_num);

    explicit operator int () const;
    explicit operator long () const;
    explicit operator short () const;

    std::string to_string() const;
    std::string get_number() const;
    std::string _is_negative() const;
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
