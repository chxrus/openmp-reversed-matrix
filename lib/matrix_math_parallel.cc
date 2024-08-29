#include "matrix_math_parallel.h"
#define THREADS 12

MatrixMathParallel::MatrixMathParallel(int rows, int columns)
    : Matrix(rows, columns) {}

void MatrixMathParallel::DecomposeLU(const Matrix &a, Matrix &l, Matrix &u) {
  int n = (int)sqrt(a.Size());

  for (int i = 0; i < n; i++) {
    l[i][i] = 1;

#pragma omp parallel for num_threads(THREADS) schedule(static)
    for (int j = i; j < n; j++) {
      u[i][j] = a[i][j];
      for (int k = 0; k < i; k++) {
        u[i][j] -= l[i][k] * u[k][j];
      }
    }

#pragma omp parallel for num_threads(THREADS) schedule(dynamic)
    for (int j = i + 1; j < n; j++) {
      l[j][i] = a[j][i];
      for (int k = 0; k < i; k++) {
        l[j][i] -= l[j][k] * u[k][i];
      }
      l[j][i] /= u[i][i];
    }
  }
}

MatrixMathParallel MatrixMathParallel::SolveLU(Matrix &l, Matrix &u,
                                               Matrix &e) {
  int n = (int)sqrt(l.Size());
  MatrixMathParallel x = MatrixMathParallel(n, n);

#pragma omp parallel for num_threads(THREADS) schedule(static)
  for (int i = 0; i < n; i++) {
    MatrixMathParallel y = MatrixMathParallel(1, n);

    for (int j = 0; j < n; j++) {
      y[j / n][j % n] = e[j][i];
      for (int k = 0; k < j; k++) {
        y[j / n][j % n] -= l[j][k] * y[k / n][k % n];
      }
    }

    for (int j = n - 1; j >= 0; j--) {
      x[j][i] = y[j / n][j % n];
      for (int k = j + 1; k < n; k++) {
        x[j][i] -= u[j][k] * x[k][i];
      }
      x[j][i] /= u[j][j];
    }
  }

  return x;
}

MatrixMathParallel MatrixMathParallel::Reversal(const Matrix &origin) {
  int n = origin.get_rows();
  int m = origin.get_columns();

  MatrixMathParallel u = MatrixMathParallel(n, m);
  MatrixMathParallel l = MatrixMathParallel(n, m);
  MatrixMathParallel e = MatrixMathParallel::Identity(n);

  MatrixMathParallel::DecomposeLU(origin, l, u);

  MatrixMathParallel reversal = MatrixMathParallel::SolveLU(l, u, e);

  return reversal;
}

MatrixMathParallel MatrixMathParallel::Identity(int n) {
  MatrixMathParallel a(n, n);
#pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = (i == j) ? 1 : 0;
    }
  }
  return a;
}