#include <gtest/gtest.h>
#include "RationalNumber.hpp"
#include <string>

TEST(RationalNumberTest, BasicAssertions) {
    RationalNumber a(-123, 5);
    RationalNumber b(123, 5);
    RationalNumber c(1234);
    RationalNumber one(1);

    std::cout << a << " " << b << std::endl;

    ASSERT_NE(a, b);
    ASSERT_EQ(-a, b);
    ASSERT_LT(a, c);
    ASSERT_LE(a, b);
    ASSERT_GT(c, a);
    ASSERT_GE(c, a);

    ASSERT_EQ(a + b, RationalNumber(0));
    ASSERT_EQ(a - b, RationalNumber(-246, 5));
    ASSERT_EQ(a / b, RationalNumber(-1));
    ASSERT_EQ(a * -1, b);
    ASSERT_TRUE(++a == a + 1);
    ASSERT_TRUE(a - 1 == a++);
    ASSERT_TRUE(--a == a - 1);
    ASSERT_TRUE(a + 1 == a--);

    ASSERT_EQ(round(b), RationalNumber(25));
    ASSERT_EQ(floor(b), RationalNumber(24));

}