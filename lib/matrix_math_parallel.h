#ifndef MATRIX_MATH_PARALLEL
#define MATRIX_MATH_PARALLEL

#include <omp.h>

#include "matrix.h"

class MatrixMathParallel : public Matrix {
 public:
  // Methods
  MatrixMathParallel(int, int);

  // Static
  static MatrixMathParallel Reversal(const Matrix &);
  static MatrixMathParallel Identity(int);

 private:
  // Static
  static void DecomposeLU(const Matrix &, Matrix &, Matrix &);
  static MatrixMathParallel SolveLU(Matrix &, Matrix &, Matrix &);
};

#include "matrix_math_parallel.cc"

#endif
