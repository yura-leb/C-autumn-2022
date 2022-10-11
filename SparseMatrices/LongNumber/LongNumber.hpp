#ifndef LONG_NUMBER_HPP
#define LONG_NUMBER_HPP

#include <string>
#include <algorithm>
/**
 * LongNumber class with numbers representation as strings.
 */


class LongNumber {
public:
    /**
     * Default constructor.
     * 
     */
    LongNumber();
    
    /**
     * Copy constructor from other LongNumber.
     * 
     * @param  right : object to copy from.
     */
    LongNumber(const LongNumber& right);
    
    /**
     * Constructor from std::string.
     * 
     * @param str : value to construct with.
     */
    LongNumber(const std::string str);
    
    /**
     * Constructor from const char *.
     * 
     * @param right : value to construct with. 
     */
    LongNumber(const char* right) : LongNumber(std::string(right)) {}

    template<typename T>
    /**
     * Constructor from other types.
     * 
     * @param right : value to construct with.
     */
    LongNumber(const T& right) : LongNumber(std::to_string(right)) {}

    
    /**
     * Unary plus.
     * 
     * @return { LongNumber }  : same object.
     */
    LongNumber operator+() const;
    
    /**
     * Unary minus.
     * 
     * @return { LongNumber }  : object with changed sign.
     */
    LongNumber operator-() const;
    
    /**
     * Add.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }       : result of adding.
     */
    friend LongNumber operator+(const LongNumber& left, const LongNumber& right);
    
    /**
     * Substract.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }       : result of substracting.
     */
    friend LongNumber operator-(const LongNumber& left, const LongNumber& right);
    
    /**
     * Multiply.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber*}      : result of multiplying.
     */
    friend LongNumber operator*(const LongNumber& left, const LongNumber& right);
    
    /**
     * Divide.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }       : result of dividing.
     */
    friend LongNumber operator/(const LongNumber& left, const LongNumber& right);
    
    /**
     * Get remainder of division.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }       : remainder of division.
     */
    friend LongNumber operator%(const LongNumber& left, const LongNumber& right);


    
    /**
     * Operator less.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return {bool}             : true if left < right, else false.
     */
    friend bool operator<(const LongNumber& left, const LongNumber& right);
    
    /**
     * Operator less or equal.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return {bool}             : true if left <= right, else false.
     */
    friend bool operator<=(const LongNumber& left, const LongNumber& right);
    
    /**
     * Operator greater.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return {bool}             : true if left > right, else false.
     */
    friend bool operator>(const LongNumber& left, const LongNumber& right);
    
    /**
     * Operator greater or equal.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return {bool}             : true if left >= right, else false.
     */
    friend bool operator>=(const LongNumber& left, const LongNumber& right);
    
    /**
     * Operator equal.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return {bool}             : true if left == right, else false.
     */
    friend bool operator==(const LongNumber& left, const LongNumber& right);
    
    /**
     * Operator not equal.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return {bool}             : true if left != right, else false.
     */
    friend bool operator!=(const LongNumber& left, const LongNumber& right);
    
    /**
     * Copy operator.
     * 
     * @param  right : object to copy from.
     * @return { LongNumber }       : this object.
     */
    LongNumber operator=(const LongNumber& right);
    
    /**
     * Add right to left and save to left.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }       : left.
     */
    friend LongNumber operator+=(LongNumber& left, const LongNumber& right);
    
    /**
     * Substract right from left and save to left.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }       : left.
     */
    friend LongNumber operator-=(LongNumber& left, const LongNumber& right);
    
    /**
     * Multiply left to right and save to left.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber }      : left.
     */
    friend LongNumber operator*=(LongNumber& left, const LongNumber& right);
    
    /**
     * Divide left on right and save to left.
     * 
     * @param  left  : left operand.
     * @param  right : right operand.
     * @return { LongNumber } : left.
     */
    friend LongNumber operator/=(LongNumber& left, const LongNumber& right);

    
    /**
     * Fing greatest comon divider. Uses euclidean algorithm.
     * 
     * @param  a : first operand.
     * @param  b : second operand.
     * @return { LongNumber }   : greatest common divider.
     */
    friend LongNumber gcd(const LongNumber& a, const LongNumber& b);
    
    /**
     * Prefix increment.
     * 
     * @return { LongNumber &}  : this object increased by 1.
     */
    LongNumber& operator++();
    
    /**
     * Prefix decrement.
     * 
     * @return { LongNumber &}  : this object decreased by 1.
     */
    LongNumber& operator--();
    
    /**
     * Postfix increment.
     * 
     * @return { LongNumber }    : this object increased by 1. 
     */
    LongNumber operator++(int);
    
    /**
     * Postfix decrement.
     * 
     * @return { LongNumber }    : this object decreased by 1. 
     */
    LongNumber operator--(int);


    
    /**
     * Print to std::ostream.
     * 
     * @param str : stream to write to.
     * @param long_number : number to write.
     * @return {std::ostream &} : stream with long_number written.
     */
    friend std::ostream & operator<<(std::ostream & str, LongNumber long_number);
    
    /**
     * Cast to bool.
     * 
     * @return {bool}  : true if number != 0, else false.
     */
    explicit operator bool () const;

    explicit operator short () const;
    explicit operator int () const;
    explicit operator long () const;

    
    /**
     * Cast to string.
     * 
     * @return {std::string}  : string with LongNumber value.
     */
    std::string to_string() const;
    
    /**
     * Get number field.
     * 
     * @return {std::string}  : number field value.
     */
    std::string get_number() const;
    
    /**
     * Get sign of number.
     * 
     * @return {bool}  : true if number < 0, else false.
     */
    bool _is_negative() const;
    
    /**
     * Remove leading zeros from string representation.
     */
    void remove_leading_zeros();


    
    /**
     * Get positive value of long_number.
     * 
     * @param  long_number : value.
     * @return { LongNumber } : positive value.
     */
    friend const LongNumber abs(const LongNumber& long_number);

private:
    
    /**
     * Value of LongNumber. 
     */
    std::string number;
    
    /**
     * Sign of LongNumber. 
     * true if LongNumber < 0, else false. 
     */
    bool is_negative;
};

#endif