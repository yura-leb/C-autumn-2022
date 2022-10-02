#include <cmath>
#include <climits>
#include <numeric>

template <typename type_real = double, typename type_imag = type_real>
class ComplexNumber {
private:
    type_real real;
    type_imag imag;

public:
    ComplexNumber(const ComplexNumber& right);
    ComplexNumber(type_real real, type_imag imag);

    const ComplexNumber operator+(const ComplexNumber& right) const;
    const ComplexNumber operator-(const ComplexNumber& right) const;
    const ComplexNumber operator*(const ComplexNumber& right) const;
    const ComplexNumber operator/(const ComplexNumber& right) const;

    template <typename T>
    const ComplexNumber operator+(const T& right) const;
    template <typename T>
    const ComplexNumber operator-(const T& right) const;
    template <typename T>
    const ComplexNumber operator*(const T& right) const;
    template <typename T>
    const ComplexNumber operator/(const T& right) const;
    

    friend bool operator<(const ComplexNumber& left, const ComplexNumber& right);
    friend bool operator<=(const ComplexNumber& left, const ComplexNumber& right);
    friend bool operator>(const ComplexNumber& left, const ComplexNumber& right);
    friend bool operator>=(const ComplexNumber& left, const ComplexNumber& right);
    friend bool operator==(const ComplexNumber& left, const ComplexNumber& right);
    friend bool operator!=(const ComplexNumber& left, const ComplexNumber& right);
    friend bool operator==(const ComplexNumber& left, const ComplexNumber& right);

    ComplexNumber& operator=(const ComplexNumber& right);
    friend ComplexNumber& operator+=(ComplexNumber& left, const ComplexNumber& right);
    friend ComplexNumber& operator-=(ComplexNumber& left, const ComplexNumber& right);

    friend const ComplexNumber& operator++(ComplexNumber& rat_num);
    friend const ComplexNumber& operator--(ComplexNumber& rat_num);

    explicit operator int () const;
    explicit operator long () const;
    explicit operator short () const;

    auto get_radius_vector();
    void print();
};
