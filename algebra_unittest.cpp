#include <iostream>
#include <gtest/gtest.h>
#include "matrix.h"
#include "vector.h"


TEST(MatrixOperators,MatrixNEQ){
	AlgebraTAU::matrix<double> M1({
		{8, 5, 5, 9, 7},
		{9, 1, 2, 2, 5},
		{8, 0, 7, 4, 7},
		{6, 9, 1, 9, 2}
	});

	AlgebraTAU::matrix<double> M2({
		{9, 3, 7, 3, 5},
		{1, 3, 3, 4, 4},
		{7, 9, 4, 9, 9},
		{9, 8, 6, 6, 5}
	});

	EXPECT_TRUE(M1 != M2);
}

TEST(MatrixOperators,MatrixEQ){
	AlgebraTAU::matrix<double> M1({
		{8, 5, 5, 9, 7},
		{9, 1, 2, 2, 5},
		{8, 0, 7, 4, 7},
		{6, 9, 1, 9, 2}
	});

	AlgebraTAU::matrix<double> M2({
		{8, 5, 5, 9, 7},
		{9, 1, 2, 2, 5},
		{8, 0, 7, 4, 7},
		{6, 9, 1, 9, 2}
	});

	EXPECT_TRUE(M1 == M2);
}

TEST(MatrixOperators,MatrixMultiplication){
	AlgebraTAU::matrix<double> M1({
		{0,1,2},
		{3,4,5}
	});
	AlgebraTAU::matrix<double> M2({
		{0,1},
		{2,3},
		{4,5}
	});
	AlgebraTAU::matrix<double> res({
		{10,13},
		{28,40}
	});

	EXPECT_EQ(M1*M2,res);
}


TEST(MatrixMethods,GaussianElimination){
	AlgebraTAU::matrix<double> M({
		{1, 2, 2, 0, 5, 1, 7, 4},
		{9, 7, 5, 2, 1, 9, 3, 1},
		{7, 2, 4, 4, 4, 5, 9, 3},
		{5, 8, 6, 5, 9, 8, 8, 8}
	});

	M.gaussian_elimination();
	EXPECT_TRUE(is_upper_triangular(M));
}


TEST(MatrixMethods,TransposeTranpose){
	AlgebraTAU::matrix<double> M({
		{1, 2, 2, 0, 5, 1, 7, 4},
		{9, 7, 5, 2, 1, 9, 3, 1},
		{7, 2, 4, 4, 4, 5, 9, 3},
		{5, 8, 6, 5, 9, 8, 8, 8}
	});

	EXPECT_EQ(M,M.transpose().transpose());
}


int main(int argc, char const *argv[])
{
  testing::InitGoogleTest(&argc,(char**)(argv));
  return RUN_ALL_TESTS();
}