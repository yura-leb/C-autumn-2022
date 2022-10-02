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
    
    explicit operator int () const;
    explicit operator long () const;
    explicit operator short () const;

    const type_real& get_real() const;
    const type_imag& get_imag() const;

    auto get_radius_vector() const;
};
