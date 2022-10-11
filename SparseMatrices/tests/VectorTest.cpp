#include <gtest/gtest.h>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "RationalNumber.hpp"
#include "ComplexNumber.hpp"
#include <string>
#include "Parser.hpp"

TEST(VectorTest, RationalNumberVectorTest) {
    Vector<RationalNumber> a("../vector_example.txt");
    Matrix<RationalNumber> m(5, 5);
    Vector<RationalNumber> ident_vector(1, 5);
    Vector<RationalNumber> zero_6_vector(0, 6);
    Vector<RationalNumber> zero_5_vector(0, 5);
    ASSERT_THROW(Vector<RationalNumber> t("no_such_file.txt"), FileNotFound);

    ASSERT_EQ(a.to_string(), (a - zero_5_vector).to_string());
    ASSERT_THROW(a(10), OutOfRange);
    ASSERT_THROW(zero_6_vector * m, DifferentSizes);
    ASSERT_EQ((a * m).to_string(), a.to_string());
    ASSERT_EQ((a * 0).to_string(), zero_5_vector.to_string());
    a[2] = RationalNumber(12346718);
    ASSERT_THROW(a[10] = RationalNumber(12346718), OutOfRange);
}
