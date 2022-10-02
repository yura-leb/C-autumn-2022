#include "Vector.h"

template <typename T>
Vector<T>::Vector(const Vector& vec) {
    dictionary = vec.dictionary;
    eps = vec.eps;
    len = vec.len;
}

template <typename T>
Vector<T>::Vector(const std::map<int, T>& dictionary, double eps, int len) {
    this->dictionary = dictionary;
    this->eps = eps;
    this->len = len;
}

template <typename T>
bool Vector<T>::is_zero(T num) {
    return -eps < num && num < eps;
}

template <typename T>
const T& Vector<T>::operator()(int i){
    
}


template <typename T>
const Vector<T> Vector<T>::operator+(const Vector<T>& right) const {
    for (int i=0; i < len; i++) {

    }
}
