#include <gtest/gtest.h>
#include "LongNumber.hpp"
#include <string>

TEST(LongNumberTest, BasicAssertions) {
  LongNumber a(-123);
  LongNumber b("123");

  std::cout << a << " " << b << std::endl;

  ASSERT_NE(a, b);
  ASSERT_EQ(abs(a), abs(b));
  ASSERT_LT(a, b);
  ASSERT_LE(a, b);
  ASSERT_GT(b, a);
  ASSERT_GE(abs(b), abs(a));

  ASSERT_EQ(a + b, LongNumber(0));
  ASSERT_EQ(a - b, LongNumber(std::string("-246")));
  ASSERT_EQ(a / b, LongNumber(-1));
  ASSERT_EQ(a * -1, b);
  ASSERT_EQ(++a, a + 1);
  ASSERT_TRUE(a._is_negative());
}
