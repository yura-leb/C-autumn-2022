#ifndef COMPLEX_NUMBER_HPP
#define COMPLEX_NUMBER_HPP

#include <climits>
#include "BadCast.hpp"

template <typename type_real = double, typename type_imag = type_real>
class ComplexNumber {
private:
    type_real real;
    type_imag imag;

public:
    ComplexNumber() {
        real = type_real(0);
        imag = type_imag(0);
    }

    ComplexNumber(const std::string&, const std::string&) { // never used
    }

    ComplexNumber(const std::string&) { // never used
    }

    ComplexNumber(const ComplexNumber& right) {
        real = right.real;
        imag = right.imag;
    }

    ComplexNumber(type_real real, type_imag imag) {
        this->real = real;
        this->imag = imag;
    }

    ComplexNumber(type_real real) {
        this->real = real;
        this->imag = 0;
    }

    ComplexNumber operator+(const ComplexNumber& right) const {
        return ComplexNumber<type_real, type_imag>(real + right.real, imag + right.imag);
    }

    ComplexNumber operator-(const ComplexNumber& right) const {
        return ComplexNumber<type_real, type_imag>(real - right.real, imag - right.imag);
    }

    ComplexNumber operator*(const ComplexNumber& right) const {
        type_real result_real = real * right.real - imag * right.imag;
        type_imag result_imag = real * right.imag + imag * right.real;
        return ComplexNumber<type_real, type_imag>(result_real, result_imag);
    }

    ComplexNumber operator/(const ComplexNumber& right) const {
        type_real result_real = (real * right.real + imag * right.imag) / (right.real * right.real + right.imag * right.imag);
        type_imag result_imag = (imag * right.real - real * right.imag) / (right.real * right.real + right.imag * right.imag);
        return ComplexNumber<type_real, type_imag>(result_real, result_imag);
    }
    
    ComplexNumber operator-() const {
        return ComplexNumber<type_real, type_imag>(-real, -imag);
    }

    template <typename ttype_real, typename ttype_imag>
    friend bool operator< (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend bool operator<= (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend bool operator> (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend bool operator>= (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend bool operator== (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend bool operator!= (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend bool operator== (const ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);


    ComplexNumber& operator=(const ComplexNumber& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend ComplexNumber<ttype_real, ttype_imag>& operator+=(ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);
    
    template <typename ttype_real, typename ttype_imag>
    friend ComplexNumber<ttype_real, ttype_imag>& operator-=(ComplexNumber<ttype_real, ttype_imag>& left, const ComplexNumber<ttype_real, ttype_imag>& right);

    template <typename ttype_real, typename ttype_imag>
    friend const ComplexNumber<ttype_real, ttype_imag>& operator++(ComplexNumber<ttype_real, ttype_imag>& rat_num);
    
    template <typename ttype_real, typename ttype_imag>
    friend const ComplexNumber<ttype_real, ttype_imag>& operator--(ComplexNumber<ttype_real, ttype_imag>& rat_num);

    template<typename ttype_real, typename ttype_imag>
    friend std::ostream & operator<<(std::ostream & str, ComplexNumber<ttype_real, ttype_imag> const & number);
    
    std::string to_string() const {
        return std::to_string(real) + " " + std::to_string(imag) + "i";
    }
    

    explicit operator int () const;
    explicit operator long () const;
    explicit operator short () const;

    const type_real& get_real() const;
    const type_imag& get_imag() const;

    auto get_radius_vector() const {
        return real * real + imag * imag;
    }

    bool is_zero(double eps) {
        return (-eps < get_radius_vector() && get_radius_vector() < eps); 
    }
};

template<typename type_real, typename type_imag>
bool operator<(const ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    return left.get_radius_vector() < right.get_radius_vector();
}

template<typename type_real, typename type_imag>
bool operator<=(const ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    return left.get_radius_vector() <= right.get_radius_vector();
}

template<typename type_real, typename type_imag>
bool operator>(const ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    return left.get_radius_vector() > right.get_radius_vector();
}

template<typename type_real, typename type_imag>
bool operator>=(const ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    return left.get_radius_vector() >= right.get_radius_vector();
}

template<typename type_real, typename type_imag>
bool operator==(const ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    return left.get_radius_vector() == right.get_radius_vector();
}

template<typename type_real, typename type_imag>
bool operator!=(const ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    return left.get_radius_vector() != right.get_radius_vector();
}

// assignment

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>& ComplexNumber<type_real, type_imag>::operator=(const ComplexNumber<type_real, type_imag>& right) {
    if (this == &right) {
        return *this;
    }

    real = right.real;
    imag = right.imag;
    return *this;
}

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>& operator+=(ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    left = left + right;
    return left;
}

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>& operator-=(ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    left = left - right;
    return left;
}

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>& operator*=(ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    left = left * right;
    return left;
}

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>& operator/=(ComplexNumber<type_real, type_imag>& left, const ComplexNumber<type_real, type_imag>& right) {
    left = left / right;
    return left;
}

template<typename type_real, typename type_imag>
const ComplexNumber<type_real, type_imag>& operator++(ComplexNumber<type_real, type_imag>& complex) {
    complex.real += 1;
    return complex;
}

template<typename type_real, typename type_imag>
const ComplexNumber<type_real, type_imag>& operator--(ComplexNumber<type_real, type_imag>& complex) {
    complex.real -= 1;
    return complex;
}


template<typename type_real, typename type_imag>
const type_real& ComplexNumber<type_real, type_imag>::get_real() const {
    return real;
}

template<typename type_real, typename type_imag>
const type_imag& ComplexNumber<type_real, type_imag>::get_imag() const {
    return imag;
}



template<typename type_real, typename type_imag>
std::ostream& operator<<(std::ostream & str, ComplexNumber<type_real, type_imag> const & number) {
  str << number.to_string();
  return str;
}

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>::operator int() const {
    if ((INT_MIN * imag < real) && (real < INT_MAX * static_cast<long long>(imag))) {
        return real / static_cast<long long>(imag);
    } else {
        throw BadCast("Int cast error");
    }
} 

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>::operator long () const {
    if ((static_cast<long long>(LONG_MIN * imag) < real) && (real < static_cast<long long>(LONG_MAX * imag))) {
        return static_cast<long>(real / imag);
    } else {
        throw BadCast("Long cast error");
    }
} 

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>::operator short () const {
    if ((static_cast<long long>(SHRT_MIN * imag) < real) && (real < static_cast<long long>(SHRT_MAX * imag))) {
        return static_cast<short>(real / imag);
    } else {
        throw BadCast("Short cast error");
    }
}

#endif
