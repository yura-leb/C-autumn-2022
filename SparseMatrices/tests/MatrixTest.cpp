#include <gtest/gtest.h>
#include "Matrix.hpp"
#include "RationalNumber.hpp"
#include "ComplexNumber.hpp"
#include <string>
#include "Parser.hpp"

TEST(MatrixTest, RationalNumberMatrixTest) {
    Matrix<RationalNumber> a("../matrix_example.txt");
    Matrix<RationalNumber> ident_matrix(5, 5);
    Matrix<RationalNumber> zero_6_matrix(0, 6, 6);
    Matrix<RationalNumber> zero_5_matrix(0, 5, 5);
    ASSERT_THROW(Matrix<RationalNumber> t("no_such_file.txt"), FileNotFound);
    Matrix_coords coords{1, 1, a.get_hight(), a.get_width()};
    MatrixProxy<RationalNumber> mp(&a, coords);
    Matrix b(mp);

    ASSERT_EQ(mp(1,1), a(1,1));
    ASSERT_EQ(mp(5,5), a(5,5));
    ASSERT_EQ(a.to_string(), b.to_string());
    ASSERT_THROW(a(10, 15), OutOfRange);
    ASSERT_THROW(a * zero_6_matrix, DifferentSizes);
    ASSERT_EQ(a.to_string(), (b * ident_matrix).to_string());
    ASSERT_EQ((a-b).to_string(), zero_5_matrix.to_string());
    std::pair p = {1, 1};
    a[std::pair{1, 1}] = RationalNumber(1);
    b[std::pair{1,1}] = RationalNumber(1);
    ASSERT_EQ(a.to_string(), b.to_string());
}

TEST(MatrixTest, ComplexNumberMatrixTest) {
    Matrix<ComplexNumber<int>> a("../complex_matrix_example.txt");
    Matrix<ComplexNumber<int>> ident_matrix(5, 5);
    Matrix<ComplexNumber<int>> zero_6_matrix(0, 6, 6);
    Matrix<ComplexNumber<int>> zero_5_matrix(0, 5, 5);
    Matrix_coords coords(1, 1, a.get_hight(), a.get_width());
    MatrixProxy<ComplexNumber<int>> mp(&a, coords);
    Matrix b(mp);

    ASSERT_EQ(mp(1,1), a(1,1));
    ASSERT_EQ(mp(5,5), a(5,5));
    ASSERT_EQ(a.to_string(), b.to_string());
    ASSERT_THROW(a(10, 15), OutOfRange);
    ASSERT_THROW(a * zero_6_matrix, DifferentSizes);
    ASSERT_EQ(a.to_string(), (b * ident_matrix).to_string());
    ASSERT_EQ((a-b).to_string(), zero_5_matrix.to_string());
}

TEST(MatrixTest, ComplexDoubleNumberMatrixTest) {
    Matrix<ComplexNumber<double>> a("../double_matrix_example.txt");
    Matrix<ComplexNumber<double>> ident_matrix(5, 5);
    Matrix<ComplexNumber<double>> zero_6_matrix(0, 6, 6);
    Matrix<ComplexNumber<double>> zero_5_matrix(0, 5, 5);
    Matrix_coords coords(1, 1, a.get_hight(), a.get_width());
    MatrixProxy<ComplexNumber<double>> mp(&a, coords);
    Matrix b(mp);

    ASSERT_EQ(mp(1,1), a(1,1));
    ASSERT_EQ(mp(5,5), a(5,5));
    ASSERT_EQ(a.to_string(), b.to_string());
    ASSERT_THROW(a(10, 15), OutOfRange);
    ASSERT_THROW(a * zero_6_matrix, DifferentSizes);
    ASSERT_EQ(a.to_string(), (b * ident_matrix).to_string());
    ASSERT_EQ((a-b).to_string(), zero_5_matrix.to_string());
}
