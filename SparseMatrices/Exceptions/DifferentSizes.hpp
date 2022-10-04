#ifndef DIFFERENT_SIZES_HPP
#define DIFFERENT_SIZES_HPP

#include "TwoParamsException.hpp"

class DifferentSizes : public TwoParamsException {
public:
    using TwoParamsException::TwoParamsException;
};

#endif
