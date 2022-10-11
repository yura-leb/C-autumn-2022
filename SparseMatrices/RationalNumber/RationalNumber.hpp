#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <cmath>
#include <climits>
#include <numeric>
#include "LongNumber.hpp"


class RationalNumber {
private:

/**
 * Numerator of Rational number. 
 */
    LongNumber numerator;
/**
 * Denominator of Rational number. Always > 0.
 */
    LongNumber denominator;

public:

    /**
     * Default constructor. 
     * 
     */
    RationalNumber();
    
    /**
     * Copy constructor from other Rational number. 
     * 
     * @param  right : other rational number.
     */
    RationalNumber(const RationalNumber& right);
    
    /**
     * Constructor from two numbers. 
     * 
     * @param  numerator   : numerator of rational number.
     * @param  denominator : denominator of rational number.
     */
    RationalNumber(const LongNumber& numerator, const LongNumber& denominator);
    
    /**
     * Constructor from string. 
     * 
     * @param  right : string representation of number. If right contains '/', then left part of right is numerator, right part is denominator.
     */
    RationalNumber(std::string right);
    
    /**
     * Constructor from number. 
     * 
     * @param  num : number.
     */
    RationalNumber(int64_t num);

    
    /**
     * Add Rational number.
     * 
     * @param  right             : other Rational number. 
     * @return {RationalNumber}  : result of operation.
     */
    RationalNumber operator+(const RationalNumber& right) const;
    
    /**
     * Substract other Rational number.
     * 
     * @param  right             : other Rational number. 
     * @return {RationalNumber}  : result of operation.
     */
    RationalNumber operator-(const RationalNumber& right) const;
    
    /**
     * Multiply Rational numbers.
     * 
     * @param  right             : other Rational number. 
     * @return {RationalNumber}  : result of operation.
     */
    RationalNumber operator*(const RationalNumber& right) const;
    
    /**
     * Divide Rational numbers.
     * 
     * @param  right             : other Rational number. 
     * @return {RationalNumber}  : result of operation.
     */
    RationalNumber operator/(const RationalNumber& right) const;
    
    /**
     * Unary minus.
     * 
     * @return {RationalNumber}  : this object with changed sign.
     */
    RationalNumber operator-() const;

    
    /**
     * Operator Less.
     * 
     * @param  left    : left operand.
     * @param  right   : right operand.
     * @return {bool}  : result of comparing.
     */
    friend bool operator<(const RationalNumber& left, const RationalNumber& right);
    
    /**
     * Operator less or equal.
     * 
     * @param  left    : left operand.
     * @param  right   : right operand.
     * @return {bool}  : result of comparing.
     */
    friend bool operator<=(const RationalNumber& left, const RationalNumber& right);
    
    /**
     * Operator greater.
     * 
     * @param  left    : left operand.
     * @param  right   : right operand.
     * @return {bool}  : result of comparing.
     */
    friend bool operator>(const RationalNumber& left, const RationalNumber& right);
    
    /**
     * Operator greater or equal.
     * 
     * @param  left    : left operand.
     * @param  right   : right operand.
     * @return {bool}  : result of comparing.
     */
    friend bool operator>=(const RationalNumber& left, const RationalNumber& right);
    
    /**
     * Operator equal.
     * 
     * @param  left    : left operand.
     * @param  right   : right operand.
     * @return {bool}  : result of comparing.
     */
    friend bool operator==(const RationalNumber& left, const RationalNumber& right);
    
    /**
     * Operator not equal.
     * 
     * @param  left    : left operand.
     * @param  right   : right operand.
     * @return {bool}  : result of comparing.
     */
    friend bool operator!=(const RationalNumber& left, const RationalNumber& right);
    

    
    /**
     * Copy operator.
     * 
     * @param  right             : other Rational number.
     * @return {RationalNumber}  : this object.
     */
    RationalNumber& operator=(const RationalNumber& right);
    
    /**
     * Add Rational number right and save to left.
     * 
     * @param  left              : left operand.
     * @param  right             : right operand.
     * @return {RationalNumber}  : left.
     */
    friend RationalNumber& operator+=(RationalNumber& left, const RationalNumber& right);
    
    /**
     * Substract Rational number right and save to left.
     * 
     * @param  left              : left operand.
     * @param  right             : right operand.
     * @return {RationalNumber}  : left. 
     */
    friend RationalNumber& operator-=(RationalNumber& left, const RationalNumber& right);

    /**
     * Prefix increment.
     * 
     * @return {RationalNumber}  : this object increased by 1.
     */
    RationalNumber& operator++();
    
    /**
     * Prefix decrement.
     * 
     * @return {RationalNumber}  : this object decreased by 1.
     */
    RationalNumber& operator--();
    
    /**
     * Postfix increment.
     * 
     * @return {RationalNumber}   : this object increased by 1. 
     */
    RationalNumber operator++(int);
    
    /**
     * Postfix decrement.
     * 
     * @return {RationalNumber}   : this object decreased by 1. 
     */
    RationalNumber operator--(int);

    
    /**
     * Cast to int.
     */
    explicit operator int () const;
    
    /**
     * Cast to long.
     */
    explicit operator long () const;
    
    /**
     * Cast to short.
     */
    explicit operator short () const;
    
    /**
     * Round number to the nearest integer.
     * 
     * @param  number            : number to round.
     * @return {RationalNumber}  : rounded number.
     */
    friend RationalNumber round(const RationalNumber& number);
    
    /**
     * Discard the fractional part.
     * 
     * @param  number            : number to round.
     * @return {RationalNumber}  : rounded number.
     */
    friend RationalNumber floor(const RationalNumber& number);

    
    /**
     * Make irreducible fraction.
     * 
     * @return {RationalNumber}  : this object.
     */
    RationalNumber make_canonical();

    /**
     * Convert to string.
     * 
     * @return {std::string}  : value in string representation.
     */
    std::string to_string() const;
    
    /**
     * Condition if Rational number is near to 0.
     * 
     * @param  eps     : approximation number.
     * @return {bool}  : true if -eps < number < eps, else false.
     */
    bool is_zero(double eps) const;
    
    /**
     * Print Rational number to stream.
     * 
     * @param  str             : stream to write Rational number.
     * @param  number          : Rational number to write.
     * @return {std::ostream}  : stream. 
     */
    friend std::ostream & operator<<(std::ostream & str, RationalNumber const & number);

};

#endif
