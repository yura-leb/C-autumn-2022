#include <iostream>

#include "ComplexNumber.h"



// constructor

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>::ComplexNumber(type_real real, type_imag imag)
{
    this->real = real;
    this->imag = imag;
}

// template<typename T>
// ComplexNumber<T, T>::ComplexNumber(T real, T imag)
// {
//     this->real = real;
//     this->imag = imag;
// }

// template<>
// ComplexNumber<double, double>::ComplexNumber(double real, double imag)
// {
//     this->real = real;
//     this->imag = imag;
// }

template<typename type_real, typename type_imag>
ComplexNumber<type_real, type_imag>::ComplexNumber(const ComplexNumber& right) {
    real = right.real;
    imag = right.imag;
}

template<typename type_real, typename type_imag>
void ComplexNumber<type_real, type_imag>::print() {
    std::cout << real << " " << imag << std::endl;
}


// arithmetic

template<typename type_real, typename type_imag>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator+(const ComplexNumber<type_real, type_imag>& right) const {
    return ComplexNumber(real + right.real, imag + right.imag);
}

template<typename type_real, typename type_imag>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator-(const ComplexNumber<type_real, type_imag>& right) const {
    return ComplexNumber(real - right.real, imag - right.imag);
}

template<typename type_real, typename type_imag>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator*(const ComplexNumber<type_real, type_imag>& right) const {
    type_real result_real = real * right.real - imag * right.imag;
    type_imag result_imag = real * right.imag + imag * right.real;
    return ComplexNumber(result_real, result_imag);
}

template<typename type_real, typename type_imag>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator/(const ComplexNumber<type_real, type_imag>& right) const {
    type_real result_real = (real * right.real + imag * right.imag) / (right.real * right.real + right.imag * right.imag);
    type_imag result_imag = (imag * right.real - real * right.imag) / (right.real * right.real + right.imag * right.imag);
    return ComplexNumber(result_real, result_imag);
}


template <typename type_real, typename type_imag>
template <typename T>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator+(const T& right) const {
    return ComplexNumber(real + right, imag);
}

template <typename type_real, typename type_imag>
template <typename T>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator-(const T& right) const {
    return ComplexNumber(real - right, imag);
}

template <typename type_real, typename type_imag>
template <typename T>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator*(const T& right) const {
    return ComplexNumber(real * right, imag * right);
}

template <typename type_real, typename type_imag>
template <typename T>
const ComplexNumber<type_real, type_imag> ComplexNumber<type_real, type_imag>::operator/(const T& right) const {
    return ComplexNumber(real / right, imag / right);
}


// compare

template<typename type_real, typename type_imag>
auto ComplexNumber<type_real, type_imag>::get_radius_vector() {
    return real * real + imag * imag;
}

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
ComplexNumber<type_real, type_imag>& ComplexNumber<type_real, type_imag>::operator=(const ComplexNumber& right) {
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

// template<typename type_real, typename type_imag>
// ComplexNumber<type_real, type_imag>::operator int() const {
//     if ((INT_MIN * imag < real) && (real < INT_MAX * static_cast<long long>(imag))) {
//         return real / static_cast<long long>(imag);
//     } else {
//         // exception
//         std::cout << "Int error" << std::endl;
//         return 0;
//     }
// } 

// ComplexNumber<type_real, type_imag>::operator long () const {
//     if ((static_cast<long long>(LONG_MIN * imag) < real) && (real < static_cast<long long>(LONG_MAX * imag))) {
//         return static_cast<long>(real / imag);
//     } else {
//         // exception
//         std::cout << "Long error" << std::endl;
//         return 0;
//     }
// } 

// ComplexNumber<type_real, type_imag>::operator short () const {
//     if ((static_cast<long long>(SHRT_MIN * imag) < real) && (real < static_cast<long long>(SHRT_MAX * imag))) {
//         return static_cast<short>(real / imag);
//     } else {
//         // exception
//         std::cout << "Short error" << std::endl;
//         return 0;
//     }
// } 

