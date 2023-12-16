// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; 

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; 
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_init)
{
    Matrix* mat = new Matrix; 

    const int width = 3;
    const int height = 5;
    Matrix_init(mat, width, height);

    ASSERT_EQUAL(Matrix_width(mat), 3);
    ASSERT_EQUAL(Matrix_height(mat), 5);
    delete mat; 

    mat = new Matrix;

    const int width2 = 500;
    const int height2 = 500;
    Matrix_init(mat, width2, height2);

    ASSERT_EQUAL(Matrix_width(mat), 500);
    ASSERT_EQUAL(Matrix_height(mat), 500);
    delete mat; 

    mat = new Matrix; 

    const int width3 = 1;
    const int height3 = 1;
    Matrix_init(mat, width3, height3);

    ASSERT_EQUAL(Matrix_width(mat), 1);
    ASSERT_EQUAL(Matrix_height(mat), 1);
    delete mat;
}

TEST(test_print)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);

    *Matrix_at(mat, 0, 0) = 42;
    ostringstream expected;
    expected << "1 1\n"
        << "42 \n";
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;

    mat = new Matrix;
    Matrix_init(mat, 5, 5);

    Matrix_fill(mat,23);
    ostringstream expected1;
    expected1 << "5 5\n"
        << "23 23 23 23 23 \n"
         << "23 23 23 23 23 \n"
         << "23 23 23 23 23 \n"
         << "23 23 23 23 23 \n"
         << "23 23 23 23 23 \n";
    ostringstream actual2;
    Matrix_print(mat, actual2);
    ASSERT_EQUAL(expected1.str(), actual2.str());

    delete mat;

}

TEST(test_row)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 5, 4);

    *Matrix_at(mat, 2, 4) = 3;
    int* ptr = Matrix_at(mat, 2, 4);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);

    delete mat;


    mat = new Matrix;
    Matrix_init(mat, 5, 4);

    *Matrix_at(mat, 0, 0) = 3;
    ptr = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 0);

    delete mat;
}

TEST(test_col)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 5, 4);

    *Matrix_at(mat, 2, 4) = 3;
    int* ptr = Matrix_at(mat, 2, 4);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 4);

    delete mat;


    mat = new Matrix;
    Matrix_init(mat, 5, 4);

    *Matrix_at(mat, 0, 0) = 3;
     ptr = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

    delete mat;
}

TEST(test_fill_border)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 4, 8);
    Matrix_fill_border(mat, 20);
    for (int i = 0; i < Matrix_width(mat); ++i)
    {
        ASSERT_EQUAL(*Matrix_at(mat, 0, i), 20);
        ASSERT_EQUAL(*Matrix_at(mat, Matrix_height(mat) - 1, i), 20);
    }

    for (int i = 0; i < Matrix_height(mat); ++i)
    {
        ASSERT_EQUAL(*Matrix_at(mat, i, 0), 20);
        ASSERT_EQUAL(*Matrix_at(mat, i, Matrix_width(mat) - 1), 20);
    }
    delete mat;
}



//TEST(test_max)
//{
//    Matrix* mat = new Matrix;
//    Matrix_init(mat, 2, 4);
//    Matrix_fill(mat, 12);
//    ASSERT_EQUAL(Matrix_max(mat), 12);
//    *Matrix_at(mat, 0, 3) = 20;
//    ASSERT_EQUAL(Matrix_max(mat), 20);
//    delete mat;
//}

TEST(edge_test_max)
{
    Matrix* mat = new Matrix;
    const int width = 3;
    const int height = 3;
    Matrix_init(mat, width, height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            *Matrix_at(mat, i, j) = i *height + j;
        }
    }
    *Matrix_at(mat, 2, 2) = 99;
    delete mat;
}
TEST(test_col_min_value)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 12);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 0);
    *Matrix_at(mat, 1, 2) = 2;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 2);
    delete mat;

}
TEST(test_edge_case_col_min)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 12);
    *Matrix_at(mat, 2, 2) = 2;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 3), 2);
    *Matrix_at(mat, 2, 0) = 1;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 3), 0);
    *Matrix_at(mat, 0, 0) = 4;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 0);
    *Matrix_at(mat, 0, 2) = 2;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 2);
    delete mat;
}
TEST(test_min_value_row)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 12);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3), 12);
    *Matrix_at(mat, 1, 2) = 2;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 3), 2);

    delete mat;

}
TEST(test_edge_case_min_value)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 12);
    *Matrix_at(mat, 2, 2) = 4;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 3), 4);
    *Matrix_at(mat, 0, 2) = 3;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3), 3);
    *Matrix_at(mat, 2, 0) = 2;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 3), 2);
    *Matrix_at(mat, 0, 0) = 1;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 3), 1);
    delete mat;
}




// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
