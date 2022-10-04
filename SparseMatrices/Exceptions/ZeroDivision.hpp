#ifndef ZERO_DIVISION_HPP
#define ZERO_DIVISION_HPP

#include "TwoParamsException.hpp"

class ZeroDivision : public TwoParamsException {
public:
    using TwoParamsException::TwoParamsException;
};

#endif
