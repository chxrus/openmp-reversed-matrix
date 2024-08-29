#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "matrix.h"

class MatrixMath : public Matrix {
 public:
  // Methods
  MatrixMath(int, int);

  // Static
  static MatrixMath Reversal(const Matrix &);
  static MatrixMath Identity(int);

 private:
  // Static
  static void DecomposeLU(const Matrix &, Matrix &, Matrix &);
  static MatrixMath SolveLU(Matrix &, Matrix &, Matrix &);
};

#include "matrix_math.cc"

#endif
