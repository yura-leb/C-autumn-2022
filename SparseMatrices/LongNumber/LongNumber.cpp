#include "LongNumber.h"
#include <iostream>

LongNumber::LongNumber() {
    number = "";
    is_negative = false;
}

LongNumber::LongNumber(const LongNumber& right) {
    number = right.number;
    is_negative = right.is_negative;
}

LongNumber::LongNumber(const std::string str) {
    if (str[0] == '-') {
        number = str.substr(1, 10);
        std::reverse(number.begin(), number.end());
        is_negative = true;
    } else {
        number = str;
        std::reverse(number.begin(), number.end());
        is_negative = false;
    }
}

LongNumber::LongNumber(const char* str) : LongNumber::LongNumber(std::string(str)) {}

template <typename T>
LongNumber::LongNumber(const T right) : LongNumber::LongNumber(std::to_string(right)) {}

std::string LongNumber::to_string() const {
    std::string tmp = number;
    std::reverse(tmp.begin(), tmp.end());
    if (is_negative) {
        return "-" + tmp;
    } else {
        return tmp;
    }
}

std::ostream & operator<<(std::ostream & str, LongNumber const & long_number) {
  str << long_number.to_string();
  return str;
}

std::string LongNumber::get_number() const {
    std::string tmp = number;
    std::reverse(tmp.begin(), tmp.end());
    return tmp;
}

const LongNumber LongNumber::operator+() const {
    return LongNumber(*this);
}
 
const LongNumber LongNumber::operator-() const {
    LongNumber copy(*this);
    copy.is_negative = !copy.is_negative;
    return copy;
}

bool operator<(const LongNumber& left, const LongNumber& right) {
    if (left == right)
        return false;

    if (left.is_negative != right.is_negative) {
        return left.is_negative;
    } else if (left.is_negative && right.is_negative) {
        return (-right) < (-left);
    } else {
        if (left.number.size() != right.number.size()) {
            return left.number.size() < right.number.size();
        } else {
            for (size_t i = left.number.size()-1; i >= 0; --i) {
                if (left.number[i] != right.number[i]) {
                    return left.number[i] < right.number[i];
                }
            }
        }
    }
}


bool operator<=(const LongNumber& left, const LongNumber& right) {
    return (left < right || left == right);
}
 
bool operator>(const LongNumber& left, const LongNumber& right) {
    return !(left <= right);
}
 
bool operator>=(const LongNumber& left, const LongNumber& right) {
    return !(left < right);
}

bool operator==(const LongNumber& left, const LongNumber& right) {
    return left.is_negative == right.is_negative && left.number == right.number;
}

bool operator!=(const LongNumber& left, const LongNumber& right) {
    return !(left == right);
}


const LongNumber LongNumber::operator+(const LongNumber& right) const {
    LongNumber res;
    int digit;
    if (is_negative) {
        if (right.is_negative) return -(-(*this) + (-right));
        else return right - (-(*this));
    }
    else if (right.is_negative) return *this - (-right);


    int carry = 0; // флаг переноса из предыдущего разряда
    for (size_t i = 0; i < std::max(number.size(), right.number.size()) || carry != 0; ++i) {
        digit = carry + (i < number.size() ? number[i] : '0') + (i < right.number.size() ? right.number[i] : '0') - '0' - '0';
        if (digit >= 10) {
            res.number += digit + '0' - 10;
            carry = 1;
        } else {
            res.number += digit + '0';
            carry = 0;
        }
    }

    return res;
}

const LongNumber LongNumber::operator-(const LongNumber& right) const {
    LongNumber res;
    int digit;

    if (right.is_negative) {
        return *this + (-right);
    } else if (is_negative) {
        return -(-(*this) + right);
    } else if (*this < right) {
        return -(right - *this);
    }
    
    int carry = 0;
    for (size_t i = 0; i < number.size() || carry != 0; ++i) {
        digit =  (i < number.size() ? number[i] : '0') - carry - (i < right.number.size() ? right.number[i] : '0');

        if (digit < 0) {
            res.number += digit + '0' + 10;
            carry = 1;
        } else {
            res.number += digit + '0';
            carry = 0;
        }
    }

    res.remove_leading_zeros();
    return res;
}

const LongNumber LongNumber::operator*(const LongNumber& right) const {
    LongNumber res(0);
    LongNumber cur;

    int digit;


    for (size_t i = 0; i < right.number.size(); ++i) {
        int carry = 0;
        cur.number = std::string(i, '0');
        std::cout << "i " << right.number[i] << std::endl;
        for (size_t j = 0; j < number.size() || carry != 0; ++j) {
            std::cout << "j " << number[j] << std::endl;

            digit = ((j < number.size() ? number[j] : '0') - '0') * ((i < right.number.size() ? right.number[i] : '0') - '0') + carry;

            std::cout << "digit " << digit << std::endl;
            cur.number += (digit % 10) + '0'; 
            carry = digit / 10;
            std::cout << "cur " << cur << std::endl;
        }
        
            std::cout << "bcur " << cur << std::endl;
        res = res + cur;
    std::cout << res.number << "asdf" << std::endl;

    }

    std::cout << res.number << "asdf" << std::endl;
    res.is_negative = is_negative | right.is_negative;
    return res;
}

const LongNumber LongNumber::operator/(const LongNumber& right) const {
    LongNumber res(0);
    if (right.number == "0") {
        std::cout << "error zero dividing" << std::endl;
        return 0;
    } else if (abs(*this) < abs(right)) {
        return 0;
    }

    LongNumber left_tmp = abs(*this);
    LongNumber right_tmp = abs(right);
    std::reverse(left_tmp.number.begin(), left_tmp.number.end());
    // std::reverse(right_tmp.number.begin(), right_tmp.number.end());
    LongNumber divider = right_tmp;
    int digit;
    size_t shift = 0;
    size_t size = right_tmp.number.size();
    size_t quotient;
    LongNumber tmp, carry;

    while (shift <  left_tmp.number.size()) {
        tmp.number = left_tmp.number.substr(shift, 1) + (tmp.number == "0" ? "" : tmp.number);
        std::cout << "tmp " << tmp << std::endl;
        quotient = 0;
        right_tmp = divider;
        std::cout << "while " << tmp << " " << right_tmp << std::endl;
        while (tmp >= right_tmp) {
            ++quotient;
            right_tmp += divider;
        }
        tmp = tmp + divider - right_tmp;
        // tmp.number += std::string(size - 1, '0');
        std::cout << "tmp2 " << tmp << std::endl;

        res.number += '0' + quotient;
        std::cout << "quo " << quotient << std::endl;
        ++shift;
        std::cout << "shift " << shift << std::endl;
    }

    std::reverse(res.number.begin(), res.number.end());
    res.remove_leading_zeros();
    res.is_negative = is_negative | right.is_negative;
    return res;
}

void LongNumber::remove_leading_zeros() {
    while (number.size() > 1 && number[number.size()-1] == '0') {
        number.pop_back();
    }
    if (number.size() == 1 && number[0] == '0') is_negative = false;
}

LongNumber& LongNumber::operator=(const LongNumber& right) {
    number = right.number;
    is_negative = right.is_negative;
    return *this;
}

LongNumber& operator+=(LongNumber& left, const LongNumber& right) {
    left = left + right;
    return left;
}

LongNumber& operator-=(LongNumber& left, const LongNumber& right) {
    left = left - right;
    return left;
}

const LongNumber abs(const LongNumber& long_number) {
    return long_number.is_negative ? -long_number : long_number;
}


int main() {
    LongNumber a(0);
    std::cout << a << std::endl;
    std::string str("-902");
    LongNumber b(str);
    std::cout << "b " << b + 0 << std::endl;
    LongNumber c("-200");
    std::cout << c << std::endl;
    std::cout << (a < b) << (c < b) << (c < a) << std::endl;

    c = a + b;
    // c = -100;
    std::cout << "c " << c << std::endl;
    std::cout << " c * " << c * 10 << std::endl;
    std::cout << "c / " << c / 102 << std::endl;
    std::cout << "c / " << c / 10 << std::endl;
    std::cout << "c / " << c / 2 << std::endl;
    std::cout << "c / " << c / 15 << std::endl;
    std::cout << "c / " << c / 1500 << std::endl;

    std::cout << std::endl << "strings" << std::endl;
    std::string s("qwerty");
    std::cout << (s == "qwerty") << std::endl;
    
}