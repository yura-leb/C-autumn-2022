#include "LongNumber.hpp"
#include <iostream>
#include <climits>
#include <string>
#include "BadCast.hpp"

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


std::string LongNumber::to_string() const {
    std::string tmp = number;
    std::reverse(tmp.begin(), tmp.end());
    if (is_negative) {
        return "-" + tmp;
    } else {
        return tmp;
    }
}

std::ostream & operator<<(std::ostream & str, LongNumber long_number) {
  str << long_number.to_string();
  return str;
}

std::string LongNumber::get_number() const {
    std::string tmp = number;
    std::reverse(tmp.begin(), tmp.end());
    return tmp;
}

LongNumber LongNumber::operator+() const {
    return LongNumber(*this);
}
 
LongNumber LongNumber::operator-() const {
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


LongNumber operator+(const LongNumber& left, const LongNumber& right) {
    LongNumber res;
    int digit;
    if (left.is_negative) {
        if (right.is_negative) return -((-left) + (-right));
        else return right - (-(left));
    }
    else if (right.is_negative) return left - (-right);


    int carry = 0; // ???????? ???????????????? ???? ?????????????????????? ??????????????
    for (size_t i = 0; i < std::max(left.number.size(), right.number.size()) || carry != 0; ++i) {
        digit = carry + (i < left.number.size() ? left.number[i] : '0') + (i < right.number.size() ? right.number[i] : '0') - '0' - '0';
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

LongNumber operator-(const LongNumber& left, const LongNumber& right) {
    LongNumber res;
    int digit;

    if (right.is_negative) {
        return left + (-right);
    } else if (left.is_negative) {
        return -(-(left) + right);
    } else if (left < right) {
        return -(right - left);
    }
    
    int carry = 0;
    for (size_t i = 0; i < left.number.size() || carry != 0; ++i) {
        digit =  (i < left.number.size() ? left.number[i] : '0') - carry - (i < right.number.size() ? right.number[i] : '0');

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

LongNumber operator*(const LongNumber& left, const LongNumber& right) {
    LongNumber res(0);
    LongNumber cur;

    int digit;


    for (size_t i = 0; i < right.number.size(); ++i) {
        int carry = 0;
        cur.number = std::string(i, '0');
        for (size_t j = 0; j < left.number.size() || carry != 0; ++j) {

            digit = ((j < left.number.size() ? left.number[j] : '0') - '0') * ((i < right.number.size() ? right.number[i] : '0') - '0') + carry;

            cur.number += (digit % 10) + '0'; 
            carry = digit / 10;
        }
        
        res = res + cur;

    }

    res.is_negative = left.is_negative ^ right.is_negative;
    return res;
}

LongNumber operator/(const LongNumber& left, const LongNumber& right) {
    LongNumber res(0);
    if (right.number == "0") {
        return 0;
    } else if (abs(left) < abs(right)) {
        return 0;
    }

    LongNumber left_tmp = abs(left);
    LongNumber right_tmp = abs(right);
    std::reverse(left_tmp.number.begin(), left_tmp.number.end());
    LongNumber divider = right_tmp;
    size_t shift = 0;
    size_t size = right_tmp.number.size();
    size_t quotient;
    LongNumber tmp, carry;

    while (shift <  left_tmp.number.size()) {
        tmp.number = left_tmp.number.substr(shift, 1) + (tmp.number == "0" ? "" : tmp.number);
        quotient = 0;
        right_tmp = divider;
        while (tmp >= right_tmp) {
            ++quotient;
            right_tmp += divider;
        }
        tmp = tmp + divider - right_tmp;

        res.number += '0' + quotient;
        ++shift;
    }

    std::reverse(res.number.begin(), res.number.end());
    res.remove_leading_zeros();
    res.is_negative = left.is_negative | right.is_negative;
    return res;
}

LongNumber operator%(const LongNumber& left, const LongNumber& right) {
    LongNumber res(0);
    if (right.number == "0") {
        return 0;
    } else if (abs(left) < abs(right)) {
        return 0;
    }

    LongNumber left_tmp = abs(left);
    LongNumber right_tmp = abs(right);
    std::reverse(left_tmp.number.begin(), left_tmp.number.end());
    LongNumber divider = right_tmp;
    size_t shift = 0;
    size_t size = right_tmp.number.size();
    size_t quotient;
    LongNumber tmp, carry;

    while (shift <  left_tmp.number.size()) {
        tmp.number = left_tmp.number.substr(shift, 1) + (tmp.number == "0" ? "" : tmp.number);
        quotient = 0;
        right_tmp = divider;
        while (tmp >= right_tmp) {
            ++quotient;
            right_tmp += divider;
        }
        tmp = tmp + divider - right_tmp;

        ++shift;
    }
    res = tmp;

    res.remove_leading_zeros();
    res.is_negative = left.is_negative | right.is_negative;
    return res;
}

void LongNumber::remove_leading_zeros() {
    // std::cout << number.size() << std::endl;
    while (number.size() > 1 && number[number.size() - 1] == '0') {
        number.pop_back();
    }
    if (number.size() == 1 && number[0] == '0') 
        is_negative = false;
}

LongNumber LongNumber::operator=(const LongNumber& right) {
    number = right.number;
    is_negative = right.is_negative;
    return *this;
}

LongNumber operator+=(LongNumber& left, const LongNumber& right) {
    left = left + right;
    return left;
}

LongNumber operator-=(LongNumber& left, const LongNumber& right) {
    left = left - right;
    return left;
}

LongNumber operator*=(LongNumber& left, const LongNumber& right) {
    left = left * right;
    return left;
}

LongNumber operator/=(LongNumber& left, const LongNumber& right) {
    left = left / right;
    return left;
}

const LongNumber abs(const LongNumber& long_number) {
    return long_number.is_negative ? -long_number : long_number;
}


LongNumber::operator bool () const { 
    return number.size() != 1 || number[0] != '0';
}

LongNumber::operator long () const { 
    if (LONG_MIN <= number && number <= LONG_MAX) {
        return std::stold((is_negative ? "-" : "") + number);
    } else {
        throw BadCast("Cannot cast to long");
        return 0;
    }
}
LongNumber::operator int () const { 
    if (INT_MIN <= number && number <= INT_MAX) {
        return std::stoi((is_negative ? "-" : "") + number);
    } else {
        throw BadCast("Cannot cast to int");
        return 0;
    }
}
LongNumber::operator short () const { 
    if (SHRT_MIN <= number && number <= SHRT_MAX) {
        return std::stoi((is_negative ? "-" : "") + number);
    } else {
        throw BadCast("Cannot cast to short");
        return 0;
    }
}

bool LongNumber::_is_negative() const {
    return is_negative;
}

LongNumber gcd(const LongNumber& a, const LongNumber& b) {
    if (b > a) 
        return gcd(b, a);
    if (!bool(b)) {        
        return a;
    }
    return gcd(b, a % b);
}

LongNumber& LongNumber::operator++() {
   *this += 1;
    return *this;
}

LongNumber& LongNumber::operator--() {
    *this -= 1;
    return *this;
}

LongNumber LongNumber::operator++(int) {
    LongNumber tmp(*this);
    operator++();
    return tmp;
}
LongNumber LongNumber::operator--(int) {
    LongNumber tmp(*this);
    operator--();
    return tmp;
}