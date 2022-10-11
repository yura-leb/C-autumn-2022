#include <gtest/gtest.h>
#include "ComplexNumber.hpp"
#include <string>
#include <map>

TEST(ComplexNumberTest, BasicAssertions) {
    ComplexNumber a(-123, 5);
    ComplexNumber b(123, -5);
    ComplexNumber c(1234);
    ComplexNumber one(1);

    std::cout << a << " " << b << std::endl;

    ASSERT_NE(a, b);
    ASSERT_EQ(-a, b);
    ASSERT_LT(a, c);
    ASSERT_LE(a, b);
    ASSERT_GT(c, a);
    ASSERT_GE(c, a);

    ASSERT_EQ(a + b, ComplexNumber(0));
    ASSERT_EQ(a - b, ComplexNumber(-246, 10));
    ASSERT_EQ(a / b, ComplexNumber(-1));
    ASSERT_EQ(a * -1, b);
    ASSERT_EQ(++a, a + 1);
    ASSERT_EQ(one.get_radius_vector(), 1);

}